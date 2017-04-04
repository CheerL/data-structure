#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char c;
    struct node* next;
}node;

typedef struct str{
    node* head;
    int len;
}str;

void StrAssign(str* S, char* chars);
void StrCopy(str* S, str H);
int StrCompare(str S, str H);
int StrLength(str S);
void Concat(str* S, str H, str T);
void SubString(str* S, str H, int start, int len);
//为了方便以后用, 多实现了几个
str StrCreate();
void StrInit(str* S);
node* StrPos(str S, int pos);
void StrPrint(str S);

//返回一个结构体
str StrCreate(){
    str S;
    S.head = (node*)malloc(sizeof(node));
    S.head->next = NULL;
    S.len = 0;
    return S;
}

//字符串初始化, 释放掉所有空间
void StrInit(str* S){
    node* p = S->head->next;
    node* temp;
    while (p){
        temp = p->next;
        free(p);
        p = temp;
    }

    S->len = 0;
    S->head->next = NULL;
}


//返回S中pos位置的节点, 允许返回头节点
node* StrPos(str S, int pos){
    node* ps = S.head;
    for (int i=0; i<pos; i++){
        ps = ps->next;
    }
    return ps;
}

//输出字符串
void StrPrint(str S){
    node* p = S.head->next;
    while(p){
        printf("%c", p->c);
        p = p->next;
    }
    printf("\n");
}

void StrAssign(str* S, char* chars){
    S->len = 0;
    S->head = (node*)malloc(sizeof(node));
    S->head->next = NULL;
    node* p = S->head;

    while(*chars){
        node* temp = (node*)malloc(sizeof(node));
        temp->c = *(chars++);
        temp->next = NULL;
        p->next = temp;
        p = p->next;
        S->len ++;
    }
}

void StrCopy(str* S, str H){
    //若S是一个未初始化的或者是空串, 进行初始化
    StrInit(S);
    node* ps = S->head;
    node* ph = H.head->next;
    S->len = H.len;
    //复制
    while(ph){
        node* temp = (node*)malloc(sizeof(node));
        temp->c = ph->c;
        temp->next = NULL;
        ps->next = temp;
        ps = ps->next;
        ph = ph->next;
    }
}

int StrLength(str S){
    return S.len;
}

int StrCompare(str S, str H){
    node* ps = S.head->next;
    node* ph = H.head->next;

    while(ps && ph){
        if (ps->c != ph->c){
            return ps->c - ph->c;
        }
        else{
            ps = ps->next;
            ph = ph->next;
        }
    }
    return S.len - H.len;
}

void Concat(str* S, str H, str T){
    //先让S=H
    StrCopy(S, H);
    //再生成一个空的temp
    str temp = StrCreate();
    //然后temp=T
    StrCopy(&temp, T);
    //找到S的尾节点
    node* p = StrPos(*S, S->len);
    //S尾节点接上temp头节点的next
    p->next = temp.head->next;
    //释放temp头节点
    free(temp.head);
    S->len = H.len + T.len;
}

//把H从start开始长为len的子串用S返回
void SubString(str* S, str H, int start, int len){
    if (start<1 || start>=H.len || len<0 || len>H.len-start+1){
        printf("Fail to get substring, out of bounds\n");
        exit(-1);
    }
    //初始化S
    StrInit(S);
    S->len = len;
    node* ps = S->head;
    node* ph = StrPos(H, start);

    for (int i=0; i<len; i++){
        node* temp = (node*)malloc(sizeof(node));
        temp->c = ph->c;
        temp->next = NULL;
        ps->next = temp;
        ps = ps->next;
        ph = ph->next;
    }
}