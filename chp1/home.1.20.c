#include <stdio.h>

double poly(double* a, int n, double x);

void main(){
    //输入多项式阶数
    int n;
    printf("Please input the order of polynomial:\n");
    scanf("%d", &n);
    
    //输入多项式系数
    double a[n];
    printf("Please input coefficients of polynomial, press enter after each one:\n");
    for (int i=0; i < n; i++){
        printf("a[%d]: ", i);
        scanf("%lf", &a[i]);
    }
    //展示多项式
    printf("The polynomail is:\n");
    for (int i=0; i < n; i++){
        if (i == 0){
            printf("%lf", a[0]);
        }
        else{
            printf(" + %lf*x^%d", a[i], i);
        }
    }
    printf("\n");

    //输入x
    double x;
    printf("Please input the x:\n");
    scanf("%lf", &x);

    //计算并输出多项式的结果
    printf("The result:\n%lf", poly(a, n, x));
    return;
}

double poly(double* a, int n, double x){
    //内部定义函数, 进行递归
    double __poly(double* a, int n, double x, int i){
        if (i == 0){
            return a[0];
        }
        else if (i < n){
            return a[i] + __poly(a, n, x, i - 1) * x;
        }
        else{
            printf("Out of bound\n");
        }
    }
    //调用内部函数__poly并返回值
    return __poly(a, n, x, n-1);
}
