#include "stack.h"              //附在本章作业最后

void main(){
    //生成字符串
    Stack S = stack_create();
    TYPE str[] = "5dhjk44kjhd5@";
    printf("The string is:\n%s\n", str);
    int len = sizeof(str) / sizeof(char) - 1;
    //求出中点位置
    int half = (len-1)/2;

    for (int i=0; i<len; i++){
        //读到标志符
        if (str[i] == '@'){
            break;
        }
        //前一半压栈
        else if (i < half){
            stack_push(&S, str[i]);
        }
        //刚好中间点, 判断奇偶
        else if (i == half){
            if (len % 2){
                stack_pop(&S);
            }
        }
        //退栈, 保证栈非空
        else if (i > half && !stack_empty(S)){
            if (stack_get_top(&S) == str[i]){
                stack_pop(&S);
            }
            else{
                break;
            }
        }
        else{
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

    
    