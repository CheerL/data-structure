#include <stdio.h>
#include <stdlib.h>

/* 结构体构造 */
typedef enum Status { // 操作状态
    FAIL = -1,
    SUCCESS = 0
} Status;

typedef struct Type // 节点内部数据类型
{
    int password;
    int count;
} Type;

typedef struct Node // 节点
{
    Type data;
    struct Node *next;
} Node;

typedef struct List // 链表
{                   //
    struct Node *p; // 当前节点指针
    int size;       // 链表大小
} List;

/* 操作函数声明 */
List list_create();                      // 初始化链表
int is_empty(List L);                    // 判断链表是否为空
Status goto_next_n_node(List *L, int n); // 将当前指针后移n位
Node *get_next_n_node(List L, int n);    // 获取当前指针后n位的指针(当前指针不移动)
Node *get_before(List L);                // 获取当前节点的前驱
Type get_data(List L);                   // 获取当前节点的数据
Status insert_node(List *L, Type data);  // 向当前节点后插入节点
Status delete_node(List *L);             // 删除当前节点

/* 操作函数定义 */

/********************************************
Function name:  list_create
Purpose:        生成一个初始化的链表, 当前指针为空, 大小为0
Params:         NULL
Return:         List
********************************************/
List list_create()
{
    List L;
    L.p = NULL;
    L.size = 0;
    return L;
}

/********************************************
Function name:  is_empty
Purpose:        判断当前给定的链表是否为空
Params:
    @List       L:      要判断的链表
Return:         int
    1:          链表非空
    0:          链表为空
********************************************/
int is_empty(List L)
{
    if (L.size == 0 && L.p == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/********************************************
Function name:  goto_next_n_node
Purpose:        将链表L的当前指针后移n位
Params:
    @List*      L:      要移动的链表L的指针
    @int        n:      后移的位数
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status goto_next_n_node(List *L, int n)
{
    if (is_empty(*L))
    {
        printf("List is empty.\n");
        return FAIL;
    }
    for (int i = 0; i < n; i++)
    {
        L->p = L->p->next;
    }
    return SUCCESS;
}

/********************************************
Function name:  get_next_n_node
Purpose:        获取链表L当前指针后n位的节点的指针, 保持L的当前指针不动
Params:
    @List       L:      要从中获取的链表
    @int        n:      后移的位数
Return:         Node*
    NULL:       链表为空, 获取失败
    else:       要求的节点的指针
********************************************/
Node *get_next_n_node(List L, int n)
{
    if (is_empty(L))
    {
        printf("List is empty.\n");
        return NULL;
    }
    Node *p = L.p;
    for (int i = 0; i < n; i++)
    {
        p = p->next;
    }
    return p;
}

/********************************************
Function name:  get_before
Purpose:        获取链表L当前指针的前驱指针
Params:
    @List       L:      要从中获取的链表
Return:         Node*
    NULL:       链表为空, 获取失败
    else:       要求的节点的指针
********************************************/
Node *get_before(List L)
{
    return get_next_n_node(L, L.size - 1);
}

/********************************************
Function name:  get_data
Purpose:        获取当前节点的数据
Params:
    @List       L:      要从中获取的链表
Return:         Type
    当前节点的数据
********************************************/
Type get_data(List L)
{
    if (L.p)
    {
        return L.p->data;
    }
    else
    {
        printf("List is empty.\n");
    }
}

/********************************************
Function name:  insert_node
Purpose:        在当前节点后插入一个数据为data的节点
                并把当前指针移动到新插入的节点
Params:
    @List*      L:      要操作的链表L的指针
    @Type       data:   新节点的数据内容
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status insert_node(List *L, Type data)
{
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        return FAIL;
    }
    node->data = data;
    if (is_empty(*L))
    {
        node->next = node;
        L->p = node;
        L->size = 1;
    }
    else
    {
        node->next = L->p->next;
        L->p->next = node;
        L->p = node;
        L->size++;
    }
    return SUCCESS;
}

/********************************************
Function name:  delete_node
Purpose:        从链表从删除当前节点,
                并把当前指针移动到删除的节点的后继
Params:
    @List*      L:      要操作的链表L的指针
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status delete_node(List *L)
{
    if (is_empty(*L))
    {
        printf("List is empty.\n");
        return FAIL;
    }
    else if (L->size == 1)
    {
        free(L->p);
        L->p = NULL;
        L->size = 0;
    }
    else
    {
        Node *before = get_before(*L);
        Node *p = L->p;
        L->p = L->p->next;
        before->next = L->p;
        free(p);
        L->size--;
    }
    return SUCCESS;
}