#include <stdio.h>
#include <stdlib.h>

int func(int n);
int func_no_rec(int n);

void main(){
    int n = 92;
    printf("func with recursion:\t%d\n", func(n));
    printf("func without recursion:\t%d\n", func_no_rec(n));    
    return;
}

//会有一定程度的截断
int func(int n){
    if (n < 0){
        printf("input should be a positive number\n");
        exit(-1);
    }
    else if (n == 0){
        return n + 1;
    }
    else{
        return n * func(n/2);
    }
}

int func_no_rec(int n){
    if (n < 0){
        printf("input should be a positive number\n");
        exit(-1);
    }
    int product = 1;
    while (n){
        product *= n;
        n /= 2;
    }
    return product;
}