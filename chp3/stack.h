#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE        100
#define INCREASE        10

#define MALLOC          -1
#define EMPTYSTACK      -2

#ifndef TYPE
    #define RELOADTAG   0
    #define TYPE char
#else
    #ifndef RELOADTAG
    #define RELOADTAG   1
    #endif
#endif

typedef struct{
    TYPE* base;
    TYPE* top;
    int size;
}Stack;

Stack stack_create();
void stack_push(Stack*, TYPE);
TYPE stack_pop(Stack* S);
int stack_empty(Stack);
TYPE stack_get_top(Stack* S);

Stack stack_create(){
    Stack S;
    S.base = (TYPE*)malloc(sizeof(TYPE) * MAX_SIZE);
    if (S.base == NULL){
        printf("Fail to create List, storage allocation error\n");
        exit(MALLOC);
    }
    S.top = S.base;
    S.size = MAX_SIZE;
    return S;
}

void stack_push(Stack* S, TYPE data){
    if (S->top - S->base >= S->size){
        S->size += INCREASE;
        S->base = (TYPE*)realloc(S->base, sizeof(TYPE)*S->size);
        if (S->base == NULL){
            printf("Fail to push, storage allocation error\n");
            exit(MALLOC);
        }
    }
    *((S->top)++) = data;
}

TYPE stack_pop(Stack* S){
    if (stack_empty(*S)){
        printf("Fail to pop, empty stack\n");
        exit(EMPTYSTACK);
    }
    return *(--(S->top));
}

int stack_empty(Stack S){
    if (S.top == S.base){
        return 1;
    }
    else{
        return 0;
    }
}

TYPE stack_get_top(Stack* S){
    return *(S->top-1);
}
