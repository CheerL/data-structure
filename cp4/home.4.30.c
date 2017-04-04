#include "link_str.h"

int StrMaxRep(str S, str* H);

void main(){
    str S = StrCreate();
    str H = StrCreate();
    
    StrAssign(&S, "aaaabbbdccdddd3ddde");
    printf("The string is:\n");
    StrPrint(S);

    printf("The max repeat %d times, it is:\n", StrMaxRep(S, &H));
    StrPrint(H);
    return;
}

//求S最大重复子串, 用H返回该串, 用返回值返回位置
//代码是在链表结构的string下写成并调试的, 然后修改到顺序存储
//四个斜杠注释的表示修改的地方
int StrMaxRep(str S, str* H){
    int len = StrLength(S);
    int num_now = 0;
    int num_max = 0;

    int pos_now = 1;
    int pos_max = 0;

    ////node* p = StrPos(S, pos_now);
    ////char char_now = p->c;
    char char_now = S[1];
    char char_max;

    for (int i=0; i<len; i++){
        ////if (p->c == char_now){
        if (S[i+1] == char_now){
            num_now++;
        }
        else{
            if (num_now > num_max){
                num_max = num_now;
                char_max =char_now;
                pos_max = pos_now;
            }
            ////char_now = p->c;
            char_now = S[i+1];
            num_now = 1;
            pos_now = i;
        }
        ////p = p->next;
    }
    if (num_now > num_max){
        num_max = num_now;
        pos_max = pos_now;
        char_max =char_now;
    }
    //生成一个字符串, 也就是最大重复子串
    char temp[num_max + 1];
    for (int i=0; i<num_max; i++){
        temp[i] = char_max;
    }
    temp[num_max] = '\0';
    //给H赋值为刚才生成的字符串
    StrAssign(H, temp);
    //返回重复次数
    return pos_max;
}