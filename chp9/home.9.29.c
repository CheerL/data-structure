#include <stdio.h>
#include <stdlib.h>

#define TYPE int // 默认节点元素类型为int

/* 结构体定义 */
typedef enum Status {
    FAIL = -1,
    SUCCESS = 0
} Status;

typedef struct Node
{
    TYPE key;
    struct Node *next;
} Node;

typedef struct List
{
    Node *h;
    Node *t;
} List;

/********************************************
Function name:  search
Purpose:        搜索指定顺序表L中的元素key, 
                返回值为成功或失败, 算法采用递归
Params:
    @List       L:      要搜索的表
    @TYPE       key:    要搜索的元素
Return:         Status
    SUCCESS:    查找成功, 此时L.t即所找元素
    FAIL:       查找失败
********************************************/
Status search(List L, TYPE key)
{
    if (L.t->key == key) // 当找到, 直接返回
    {
        return SUCCESS;
    }
    else if (L.t->key > key) // 当当前元素大于目标元素
    {                        // 返回起始点h
        if (L.t != L.h)
        {
            L.t = L.h;
            search(L, key);
        }
        else // 若当前即是起始点, 停止搜索, 返回失败
        {
            return FAIL;
        }
    }
    else //当当前元素小于目标元素
    {    // 前往当前点的下一个
        if (L.t->next != NULL && L.t->next->key <= key)
        {
            L.t = L.t->next;
            search(L, key);
        }
        else // 若达到表尾或下一个值大于目标值, 返回失败
        {
            return FAIL;
        }
    }
}