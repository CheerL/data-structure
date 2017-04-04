#include "link_str.h"

void main(){
    str S = StrCreate();
    str H = StrCreate();
    str T = StrCreate();
    StrAssign(&S, "wangxi shabi");
    StrCopy(&H, S);
    Concat(&T, S, H);
    StrPrint(T);
    printf("%d", StrLength(H));
    printf("%d", StrLength(S));
    return;
}