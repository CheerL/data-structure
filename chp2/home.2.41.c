typedef struct Poly{
    int order;
    double coef;
}Poly;

#define TYPE Poly               //list.h中的TYPE是int, 这里需要修改
#include <stdio.h>
#include "list.h"

TYPE* create_Poly_from_array(double* array, int size, TYPE* polys);
void poly_equal(TYPE* a, TYPE b);
void poly_list_print(List L);
void poly_diff(List* L);

void main(){
    //生成多项式系数数组
    double array[] = {0, 3, 4, 22.1, 6, 0.5, 20, 77, 50, 28};
    int size = sizeof(array) / sizeof(double) / 2;
    TYPE polys[size];
    create_Poly_from_array(array, size, polys);
    //生成多项式链表
    int max_size = 20;
    List L = list_create_from_array(max_size, polys, size, &poly_equal);
    printf("The polynomial before:\n");
    poly_list_print(L);
    //求导
    poly_diff(&L);
    printf("The polynomial after differentiate:\n");
    poly_list_print(L);    
    return;
}

//求偏导
void poly_diff(List* L){
    Node* p = L->head->next;
    while(p != NULL){
        //对于多项式的常数项, 去掉这个结点
        //若该结点存在, 必定紧接着头结点
        if (p->data.order == 0){
            p = p->next;
            free(L->head->next);
            L->head->next = p;
            L->size --;
        }
        else{
            p->data.coef *= p->data.order;
            p->data.order --;
            p = p->next;
        }
    }
}

//好气啊, 好想重载啊, 好想用默认参数啊
TYPE* create_Poly_from_array(double* array, int size, TYPE* polys){
    for (int i=0; i < size; i++){
        Poly temp;
        temp.order = array[2*i];
        temp.coef = array[2*i+1];
        poly_equal(&(polys[i]), temp);
    }
}

//重载(???)结构体poly的等于
void poly_equal(TYPE* a, TYPE b){
    (*a).order = b.order;
    (*a).coef = b.coef;
}

//输出多项式
void poly_list_print(List L){
    Node* p = L.head->next;
    while (p != NULL){
        if (p == L.head->next){
            if (p->data.order == 0){
                printf("%lf", p->data.coef);
            }
            else{
                printf("%lf*x^%d", p->data.coef, p->data.order);
            }
        }
        else{
            printf(" + %lf*x^%d", p->data.coef, p->data.order);
        }
        p = p->next;
    }
    printf("\n");
}
