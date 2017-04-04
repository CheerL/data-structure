#include "stack.h"
#include <string.h>

void opnd_do(TYPE, Stack*);
int opnd_value(TYPE);

void main(){
    //生成通常表达式
    TYPE expression[] = "a+b*c-d/e*f";
    Stack opnd_stack = stack_create();
    //用指针来循环表达式
    TYPE* the_char = expression;
    while(*the_char){
        //当是运算符
        if (*the_char == '+' || *the_char == '-' || *the_char == '*' || *the_char == '/'){
            //进行操作并自增指针
            opnd_do(*the_char++, &opnd_stack);
        }
        //当是字母
        else if ((*the_char-'a'>=0 && *the_char-'z'<=0) || (*the_char-'A'>=0 && *the_char-'Z'<=0)){
            //输出字母并自增指针
            printf("%c", *the_char++);
        }
    }
    //退空算符栈
    while (!stack_empty(opnd_stack)){
        printf("%c", stack_pop(&opnd_stack));
    }
    return;
}

void opnd_do(TYPE the_char, Stack* opnd_stack){
    //当前算符优先级高于栈顶
    if (opnd_value(the_char) > opnd_value(stack_get_top(opnd_stack))){
        stack_push(opnd_stack, the_char);
    }
    else{
        //退栈并输出字符, 直至当前算符优先级高于栈顶
        printf("%c", stack_pop(opnd_stack));
        opnd_do(the_char, opnd_stack);
    }
}

int opnd_value(TYPE c){
    if (c == '*' || c == '/'){
        return 2;
    }
    else if (c == '+' || c == '-'){
        return 1;
    }
    else{
        return 0;
    }
}
