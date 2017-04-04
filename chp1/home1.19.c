#include <stdio.h>
#include <stdlib.h>
#include <limits.h>         //获取整型数上界INT_MAX

void array_print(int *array, int len);

void main(){
    int n = 10;             //要求个数的上界
    int ARRAYSIZE = 20;     //数组长度, 算了一下大概十几就爆掉了
    int array[ARRAYSIZE];

    //生成数组
    for (int i=1; i <= n; i++){
        //数组越界判断
        if (i > ARRAYSIZE){
            printf("Out of bounds when i = %d,\n", i);
            printf("The result before that:\n");
            array_print(array, i-1);
            exit(-1);
        }
        else if (i == 1){
            array[i-1] = 1 * 2;
        }
        else{
            //整值溢出判断
            if (array[i-2] <= INT_MAX/2/i){
                array[i-1] = array[i-2] * 2 * i;
            }
            else{
                printf("Overflow when i = %d,\n", i);
                printf("The result before that:\n");
                array_print(array, i-1);
                exit(-2);
            }
        }
    }

    //输出数组
    array_print(array, n);

    return;
}

void array_print(int *array, int len){
    //打印整型数组
    for (int i=0; i < len; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    return;
}
