#include <stdio.h>
#include "list.h"

void list_delete_cross(List*, List, List);
int list_cross(List, List, TYPE*);

void main(){
    //生成测试列表A, B
    TYPE array_A[] = {1, 2, 3, 3, 5, 44, 666, 7777};
    TYPE array_B[] = {1, 2, 3, 4, 666, 1117};
    TYPE array_C[] = {1, 2, 3, 4, 666, 1107};
    int array_size_A = sizeof(array_A) / sizeof(TYPE);
    int array_size_B = sizeof(array_B) / sizeof(TYPE);
    int array_size_C = sizeof(array_C) / sizeof(TYPE);
    int list_max_size = 20;
    List L_A = list_create_from_array(list_max_size, array_A, array_size_A);
    List L_B = list_create_from_array(list_max_size, array_B, array_size_B);
    List L_C = list_create_from_array(list_max_size, array_C, array_size_C);
    printf("L_A:\n");
    list_print(L_A);
    printf("L_B:\n");
    list_print(L_B);
    printf("L_C:\n");
    list_print(L_C);

    //删除A中的部分元素
    list_delete_cross(&L_A, L_B, L_C);
    printf("L_A after delete:\n");
    list_print(L_A);

    return;
}

void list_delete_cross(List* L_A, List L_B, List L_C){
    //取B, C中比较长的那个的size构造数组, 用于存储公共元素
    int size = (L_B.size > L_C.size)?L_B.size:L_C.size;
    TYPE result[size];
    int count = list_cross(L_B, L_C, result);

    //删除A中的B, C公共元素.
    int index = 0;
    Node* pa = L_A->head;
    Node* temp;
    while (pa->next != NULL && index < count){
        //当是公共元素, 删除
        if (pa->next->data == result[index]){
            temp = pa->next;
            pa->next = temp->next;
            free(temp);
            L_A->size --;
        }
        //当大于当前比较的公关元, 比较下一个
        else if (pa->next->data > result[index]){
            index ++;
        }
        //当大于当前比较的公关元, 指针偏移一位
        else if (pa->next->data < result[index]){
            pa = pa->next;
        }
    }
}

//找出B, C中的公共元素, 存在result中, 返回公共元素个数
int list_cross(List L_B, List L_C, TYPE* result){
    int count = 0;
    Node* pb = L_B.head->next;
    Node* pc = L_C.head->next;
    while(pb != NULL && pc != NULL){
        if (pb->data == pc->data){
            result[count] = pb->data;
            count ++;
            pb = pb->next;
            pc = pc->next;
        }
        else if (pb->data > pc->data){
            pc = pc->next;
        }
        else if (pb->data < pc->data){
            pb = pb->next;
        }
    }
    //返回公共元素计数器
    return count;
}
