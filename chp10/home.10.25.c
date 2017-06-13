#include <stdio.h>
#include <stdlib.h>

#define KEY int
#define TYPE int

typedef struct node
{
    TYPE data;
    KEY key;
    struct node *next;
} Node;

typedef struct List
{
    Node *head;
    int len;
} List;

/********************************************
Function name:  list_insert_sort
Purpose:        将链表L排序, 结果从小到大排列
Params:
    @List       L:  要排序的链表, 头指针为空, 至少有一个元素
Return:         void
********************************************/
void list_insert_sort(List L)
{
    Node *pre_p, *p, *pre_q, *q; // 4个辅助指针, p, q为主要指针
                                 // pre_p, pre_q为相应的前驱, 用于交换
    pre_p = L.head->next;        // 初始化指针p, pre_p为链表第二个元素
    p = pre_p->next;
    while (p)           // 当指针非空
    {                   //
        pre_q = L.head; // 初始化指针q, 用于循环
        q = pre_q->next;
        while (q != p)
        {
            if (p->key < q->key) // 当p的关键字较小, 交换位置
            {
                pre_p->next = p->next;
                p->next = q;
                pre_q->next = p;
                break;
            } // 否则q指针推向下一个
            pre_q = q;
            q = q->next;
        }
        if (pre_p->next == p) // 若没有发生交换, pre_ 向前推进 否则pre_p保持不变
        {
            pre_p = p;
        }
        p = pre_p->next; // p指针是pre_p的后继
    }
}