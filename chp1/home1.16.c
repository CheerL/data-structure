#include <stdio.h>

void swap(int *a, int *b);
void max(int *array, int len);
void array_print(int *array, int len);

void main(){
    int n = 3;
    int array[n];
    //输入
    printf("Please input %d integers, press enter after each one:\n", n);
    for (int i=0; i< n; i++){
        scanf("%d", &array[i]);
    }
	//排序
    max(array, n);
	//输出
    printf("rank result:\n");
    array_print(array, n);
    return;
}

void swap(int *a, int *b){
	//交换a,b
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void max(int *array, int len){
  	//输入长为n的int型数组, 进行从大到小排序
    for (int i = 0; i < len-1; i++){
        for (int j = i+1; j < len; j++){
            if (array[i] < array[j]){
                swap(&array[i], &array[j]);
            }
        }
    }
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