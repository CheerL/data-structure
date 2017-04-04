#include <stdio.h>
#include "list.h"

void list_range_delete(List* L, TYPE min, TYPE max);

void main(){
    //生成并显示测试列表
    TYPE array[] = {3, 5, 8, 235, 555, 1996};
    int array_size = sizeof(array) / sizeof(TYPE);
    int list_max_size = 10;
    List L = list_create_from_array(list_max_size, array, array_size);
    printf("L before:\n");
    list_print(L);

    //删除指定范围
    int min = 7;
    int max = 300;
    list_range_delete(&L, min, max);
    //展示结果
    printf("L after delete:\n");
    list_print(L);
    return;
}

void list_range_delete(List* L, TYPE min, TYPE max){
    Node* p = L->head;
    Node* temp;

    while(p->next != NULL){
        //当符合要求, 删除
        if (p->next->data > min && p->next->data < max){
            temp = p->next;
            p->next = temp->next;
            free(temp);
            L->size --;
        }
        //当不符合要求, 指针后移一位, 继续寻找
        else{
            p = p->next;
        }
    }
}