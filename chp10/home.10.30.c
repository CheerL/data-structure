#include <stdio.h>
#include <stdlib.h>
#include "sort_list.h"

#define STACK_TYPE int
#include "stack.h"

int partition(List *L, int low, int high, int *flag)
{
    KEY pivotkey = L->r[low].key;
    while (low < high)
    {
        while (low < high && L->r[high].key >= pivotkey)
        {
            high--;
        }
        if (low != high)
        {
            node_swap(&(L->r[low]), &(L->r[high]));
            *flag = 1;
        }
        while (low < high && L->r[low].key <= pivotkey)
        {
            low++;
        }
        if (low != high)
        {
            node_swap(&(L->r[low]), &(L->r[high]));
            *flag = 1;
        }
    }
    return low;
}

void quick_sort(List *L)
{
    Stack S = stack_create();
    int low = 1, high = L->len;
    while (low < high)
    {
        if (high - low < 3)
        {
            for (int i = low; i < high; i++)
            {
                for (int j = i + 1; j <= high; j++)
                {
                    if (L->r[j].key < L->r[i].key)
                    {
                        node_swap(&(L->r[i]), &(L->r[j]));
                    }
                }
            }
        }
        else
        {
            int flag = 0;
            int pivot_low = partition(L, low, high, &flag);
            if (flag)
            {
                if (high - pivot_low > pivot_low - low)
                {
                    stack_push(&S, pivot_low + 1);
                    stack_push(&S, high);
                    low = pivot_low - 1;
                    continue;
                }
                else
                {
                    stack_push(&S, low);
                    stack_push(&S, pivot_low - 1);
                    high = pivot_low + 1;
                    continue;
                }
            }
        }
        if (!stack_empty(S))
        {
            high = stack_pop(&S);
            low = stack_pop(&S);
        }
    }
}