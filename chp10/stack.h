#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define INCREASE 10

#define MALLOC -1
#define EMPTYSTACK -2

#ifndef STACK_TYPE
#define RELOADTAG 0
#define STACK_TYPE char
#else
#ifndef RELOADTAG
#define RELOADTAG 1
#endif
#endif

typedef struct
{
    STACK_TYPE *base;
    STACK_TYPE *top;
    int size;
} Stack;

Stack stack_create();
void stack_push(Stack *, STACK_TYPE);
STACK_TYPE stack_pop(Stack *S);
int stack_empty(Stack);
STACK_TYPE stack_get_top(Stack *S);

Stack stack_create()
{
    Stack S;
    S.base = (STACK_TYPE *)malloc(sizeof(STACK_TYPE) * MAX_SIZE);
    if (S.base == NULL)
    {
        printf("Fail to create List, storage allocation error\n");
        exit(MALLOC);
    }
    S.top = S.base;
    S.size = MAX_SIZE;
    return S;
}

void stack_push(Stack *S, STACK_TYPE data)
{
    if (S->top - S->base >= S->size)
    {
        S->size += INCREASE;
        S->base = (STACK_TYPE *)realloc(S->base, sizeof(STACK_TYPE) * S->size);
        if (S->base == NULL)
        {
            printf("Fail to push, storage allocation error\n");
            exit(MALLOC);
        }
    }
    *((S->top)++) = data;
}

STACK_TYPE stack_pop(Stack *S)
{
    if (stack_empty(*S))
    {
        printf("Fail to pop, empty stack\n");
        exit(EMPTYSTACK);
    }
    return *(--(S->top));
}

int stack_empty(Stack S)
{
    if (S.top == S.base)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

STACK_TYPE stack_get_top(Stack *S)
{
    return *(S->top - 1);
}
