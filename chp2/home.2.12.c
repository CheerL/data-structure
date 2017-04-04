#include <stdio.h>
#include "list.h"

int list_compare(List, List);

void main(){
    //生成测试列表A, B
    TYPE array_A[] = {1, 2, 3, 4, 666};
    TYPE array_B[] = {1, 2, 3, 4, 666, 7};
    int array_size_A = sizeof(array_A) / sizeof(TYPE);
    int array_size_B = sizeof(array_B) / sizeof(TYPE);
    int list_max_size = 20;
    List L_A = list_create_from_array(list_max_size, array_A, array_size_A);
    List L_B = list_create_from_array(list_max_size, array_B, array_size_B);
    printf("L_A:\n");
    list_print(L_A);
    printf("L_B:\n");
    list_print(L_B);
    //比较链表
    int compare_result = list_compare(L_A, L_B);
    //输出结果
    if (compare_result == 0){
        printf("L_A = L_B\n");
    }
    else if (compare_result == 1){
        printf("L_A > L_B\n");
    }
    else if (compare_result == -1){
        printf("L_A < L_B\n");
    }
    return;
}

int list_compare(List L_A, List L_B){
    Node* pa = L_A.head->next;
    Node* pb = L_B.head->next;

    while(pa != NULL && pb != NULL){
        //当A的值较大
        if (pa->data > pb->data){
            return 1;
        }
        //当B的值较大
        else if (pa->data < pb->data){
            return -1;
        }
        else{
            //当A, B同时为空
            if (pa->next == NULL && pb->next == NULL){
                return 0;
            }
            //当A空
            else if (pa->next == NULL){
                return -1;
            }
            //当B空
            else if (pb->next == NULL){
                return 1;
            }
            //继续迭代
            else{
                pa = pa->next;
                pb = pb->next;
            }
        }
    }
}