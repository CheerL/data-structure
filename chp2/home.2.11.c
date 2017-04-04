#include <stdio.h>
#include "list.h"		//附在本章作业的最后

void list_order_insert(List*, TYPE);

void main(){
    //生成测试列表并显示
    TYPE array[] = {3, 5, 8, 235, 555, 1996};
    int array_size = sizeof(array) / sizeof(TYPE);
    int list_max_size = 10;
    List L = list_create_from_array(list_max_size, array, array_size);
    list_print(L);              //3 5 8 235 555 1996
    //插入并显示结果
    list_order_insert(&L, 18);
    list_print(L);              //3 5 8 18 235 555 1996 
    return;
}

void list_order_insert(List* L, TYPE data){
    Node* p = L->head;

    while(p->next != NULL){
        if (p == L->head) {;}
        else if (p->data <= data && p->next->data >= data){
            break;
        }
        p = p->next;
    }

    Node* insert;
    insert = (Node*)malloc(sizeof(Node));
    //当内存分配失败, 报错
    if (insert == NULL){
        printf("Fail to create List, storage allocation error\n");
        exit(MALLOC);
    }
    insert->data = data;
    insert->next = p->next;
    p->next = insert;
    L->size ++;
}