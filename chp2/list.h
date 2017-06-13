#include <stdio.h>
#include <stdlib.h>

#define OVERFLOOR -1
#define MALLOC -2
#define OUTOFBOUND -3

#ifndef TYPE
#define TYPE int
#define RELOADTAG 0
#define list_create_from_array(max_size, array, array_size) _list_create_from_array(max_size, array, array_size, &useless)
#else
//当重新定义了TYPE的类型, 需要重载运算, 使用函数指针和宏定义
#define RELOADTAG 1
#define list_create_from_array(max_size, array, array_size, function) _list_create_from_array(max_size, array, array_size, function)
#endif

typedef struct node
{
    TYPE data;
    struct node *next;
} Node;

typedef struct
{
    Node *head;
    int max_size;
    int size;
} List;

List list_create(int);
Node *list_get_node(List, int);
void list_insert(List *, TYPE, int);
void list_print(List);
List _list_create_from_array(int max_size, TYPE *array, int array_size, void (*function)(TYPE *, TYPE));
void useless(TYPE *a, TYPE b) { ; }

List list_create(int max_size)
{
    Node *head;
    head = (Node *)malloc(sizeof(Node));
    if (head == NULL)
    {
        printf("Fail to create List, storage allocation error\n");
        exit(MALLOC);
    }
    head->next = NULL;

    List L;
    L.head = head;
    L.max_size = max_size;
    L.size = 0;

    return L;
}

Node *list_get_node(List L, int index)
{
    //当超过链表当前长度, 报错
    if (index > L.size)
    {
        printf("Fail to get node, out of list's bounds\n");
        exit(OUTOFBOUND);
    }
    //index = 0, 返回头结点, index > 0, 返回第index个元素
    Node *p = L.head;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
    }
    return p;
}

void list_insert(List *L, TYPE data, int index)
{
    //在第index个位置插入元素
    //当超过最大限定, 报错
    if (index > L->max_size)
    {
        printf("Fail to insert, out of max size\n");
        exit(OVERFLOOR);
    }

    Node *p = list_get_node(*L, index - 1);
    Node *insert;
    insert = (Node *)malloc(sizeof(Node));
    //当内存分配失败, 报错
    if (insert == NULL)
    {
        printf("Fail to create node, storage allocation error\n");
        exit(MALLOC);
    }

    insert->data = data;
    insert->next = p->next;
    p->next = insert;
    L->size++;
}

void list_print(List L)
{
    Node *p = L.head->next;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//为了重载, 连函数指针都拿出来了
List _list_create_from_array(int max_size, TYPE *array, int array_size, void (*function)(TYPE *, TYPE))
{
    List L = list_create(max_size);
    for (int i = 0; i < array_size; i++)
    {
        Node *p;
        p = (Node *)malloc(sizeof(Node));
        //当内存分配失败, 报错
        if (p == NULL)
        {
            printf("Fail to create node, storage allocation error\n");
            exit(MALLOC);
        }
        //逆序插入数组
        //TYPE != int
        if (RELOADTAG)
        {
            (*function)(&(p->data), array[array_size - i - 1]);
        }
        //TYPE == int
        else
        {
            p->data = array[array_size - i - 1];
        }
        p->next = L.head->next;
        L.head->next = p;
    }
    L.size = array_size;
    return L;
}