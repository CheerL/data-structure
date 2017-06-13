#include <stdio.h>
#include "list.h"

void list_reverse(List L);

void main()
{
    //生成并显示测试列表
    TYPE array[] = {3, 5, 8, 235, 555, 1996};
    int array_size = sizeof(array) / sizeof(TYPE);
    int list_max_size = 10;
    List L = list_create_from_array(list_max_size, array, array_size);
    printf("L before:\n");
    list_print(L);

    //逆置链表
    list_reverse(L);
    printf("L after reverse:\n");
    list_print(L);
    return;
}

void list_reverse(List L)
{
    //取下头节点
    Node *p = L.head->next;
    L.head->next = NULL;
    Node *temp;

    //当节点非空, 取下来插到头结点后
    while (p != NULL)
    {
        temp = p->next;
        p->next = L.head->next;
        L.head->next = p;
        p = temp;
    }
}