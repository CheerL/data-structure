#include "stack.h"

void main(){
    //生成字符串
    Stack S = stack_create();
    TYPE str[] = "566dsa&asd665213";
    printf("The string is:\n%s", str);
    int len = sizeof(str) / sizeof(char) - 1;
    //对字符串进行判断
    //设置标志tag, 当读到&自增
    //tag == 0, push, tag == 1, pop, tag > 1, stop
    int tag = 0;
    for (int i=0; i<len; i++){
        //读到标志符
        if (str[i] == '&'){
            tag++;
        }
        //结束
        else if (str[i] == '@'){
            break;
        }
        //压栈
        else if (tag == 0){
            stack_push(&S, str[i]);
        }
        //退栈, 保证栈非空
        else if (tag == 1 && !stack_empty(S)){
            if (stack_get_top(&S) == str[i]){
                stack_pop(&S);
            }
            else{
                break;
            }
        }
        else{
            //为了避免栈空时形如 str&rts**** 的串符合要求, 额外压入一个&
            stack_push(&S, ' ');
            break;
        }
        
    }
    //结果判断
    if (stack_empty(S)){
        printf("The string meets the requirements.\n");
    }
    else{
        printf("The string does not meet the requirements.\n");
    }
    return;
}

    
    