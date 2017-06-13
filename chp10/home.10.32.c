#include <stdio.h>
#include <stdlib.h>
#include "sort_list.h"

#define STACK_TYPE Node
#include "stack.h"

typedef enum COLOR {
    RED = 0,
    WHITE = 1,
    BLUE = 2
} COLOR;

void sort_by_color(List *L)
{
    Stack red_s, white_s, blue_s;
    red_s = stack_create();
    white_s = stack_create();
    blue_s = stack_create();
    Node temp_node;

    for (int i = 1; i < L->len; i++) // 建立3个栈, 按颜色把节点压进栈
    {
        temp_node = L->r[i];
        if (temp_node.key == RED)
        {
            stack_push(&red_s, temp_node);
        }
        else if (temp_node.key == WHITE)
        {
            stack_push(&white_s, temp_node);
        }
        else if (temp_node.key == BLUE)
        {
            stack_push(&blue_s, temp_node);
        }
        else
        {
            return;
        }
    }

    for (int i = 1; i < L->len; i++) // 按顺序退栈
    {
        if (!stack_empty(red_s))
        {
            temp_node = stack_pop(&red_s);
        }
        else if (!stack_empty(white_s))
        {
            temp_node = stack_pop(&white_s);
        }
        else if (!stack_empty(blue_s))
        {
            temp_node = stack_pop(&blue_s);
        }
        else
        {
            return;
        }
        *&(L->r[i]) = *&(temp_node); // 将对应位置的节点赋值为退栈节点;
    }
}

int main()
{
    List L;
    L.len = 7;
    L.r[1].key = WHITE;
    L.r[2].key = BLUE;
    L.r[3].key = RED;
    L.r[4].key = WHITE;
    L.r[5].key = WHITE;
    L.r[6].key = RED;

    for (int i = 1; i < L.len; i++)
        printf("%d", L.r[i].key);

    sort_by_color(&L);

    printf("\n");
    for (int i = 1; i < L.len; i++)
        printf("%d", L.r[i].key);

    return 0;
}