#include "link_str.h"					//也就是上一题的代码

node* StrPos(str S, int pos);
int KMP(str S, str H, int pos);
int KMP_next(str H, int* next);

void main(){
    str S = StrCreate();
    str H = StrCreate();
    StrAssign(&S, "ASBADABBAABADABBADADA");
    StrAssign(&H, "ADABBADADA");
    printf("%d", KMP(S, H, 1));
    return;
}

int KMP(str S, str H, int pos){
    //边界判断
    if (pos<1 || pos>StrLength(S)){
        printf("Fail to get substring, out of bounds\n");
        exit(-1);
    }
    //获取主串位置pos
    int i = pos;
    int j = 1;
    node* ps = StrPos(S, i);
    node* ph = StrPos(H, j);
    //计算next
    int next[H.len + 1];
    KMP_next(H, next);
    //开始匹配
    while(i<=S.len && j<=H.len){
        if (j==0 || ps->c == ph->c){
            i++;
            j++;
            ps = ps->next;
            ph = ph->next;
        }
        else{
            j = next[j];
            ph = StrPos(H, j);
        }
    }
    if (j>H.len){
        return i - H.len;
    }
    return 0;
}

int KMP_next(str H, int* next){
    next[0] = -1;
    next[1] = 0;

    int i = 1;
    int j = 0;
    node* ph = StrPos(H, i);
    node* _ph = StrPos(H, j);
    while (i < H.len){
        if (j == 0 || ph->c == _ph->c){
            i++;
            j++;
            ph = ph->next;
            _ph = _ph->next;
            if (ph->c != _ph->c){
                next[i] = j;
            }
            else{
                next[i] = next[j];
            }
        }
        else{
            j = next[j];
            _ph = StrPos(H, j);
        }
    }
}