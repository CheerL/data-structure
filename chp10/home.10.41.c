#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "sort_list.h"

#define STACK_TYPE Node
#include "stack.h"

/* 获取整数num的倒数第count位 */
#define DIGIT(num, count) (int)(num % (int)pow(10, count + 1)) / (int)pow(10, count)

void radix_sort(List *L)
{
    Node temp_node;
    Stack stacks[10]; // 建立10个栈, 并初始化
    for (int i = 0; i < 10; i++)
    {
        stacks[i] = stack_create();
    }
    for (int digit = 0; digit < 4; digit++) // 对位数做循环, 小于10000则最多4位
    {
        for (int i = 1; i < L->len; i++) // 按key的倒数第digit位压进栈
        {
            temp_node = L->r[i];
            stack_push(&stacks[DIGIT(temp_node.key, digit)], temp_node);
        }

        int stack_num = 9;
        for (int i = L->len - 1; i > 0; i--) // 逆序出栈
        {
            temp_node = stack_pop(&stacks[stack_num]);
            if (stack_empty(stacks[stack_num]) && stack_num > 0)
            {
                stack_num--;
            }
            *&(L->r[i]) = *&(temp_node); // 赋值
        }
    }
}