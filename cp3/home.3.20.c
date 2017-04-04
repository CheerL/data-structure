#include <stdio.h>
#include <time.h>           //提供time()函数的原型
#include <stdlib.h>         //提供rand(),srand()函数的原型

#define COLOR_RANGE 2
#define WIDTH 10
#define HEIGHT 20
//生成随机数
#define random rand() % COLOR_RANGE

void trans_color(int x, int y, int color_before, int color_trans, int* graph);
void create_graph(int* graph);
void show_graph(int* graph);
int rand_int(int);

void main(){
    //生成图片
    int* graph = (int*)malloc(sizeof(int) * WIDTH * HEIGHT);
    create_graph(graph);
    printf("The graph before:\n");
    show_graph(graph);

    //设定点(x,y)
    int x = 0;
    int y = 3;
    int color_before = *(graph + x*HEIGHT + y);
    int color_trans;
    if (color_before == COLOR_RANGE - 1){
        color_trans = 0;
    }
    else{
        color_trans = color_before + 1;
    }

    //改变颜色
    trans_color(x, y, color_before, color_trans, graph);

    //显示修改后图片
    printf("The graph after trans:\n");
    show_graph(graph);
    return;
}

void trans_color(int x, int y, int color_before, int color_trans, int* graph){
    if (x >= 0 && x < WIDTH && y >=0 && y < HEIGHT){
        if (*(graph + x*HEIGHT + y) == color_before){
            *(graph + x*HEIGHT + y) = color_trans;
            //递归吧少年
            trans_color(x+1, y, color_before, color_trans, graph);
            trans_color(x-1, y, color_before, color_trans, graph);
            trans_color(x, y+1, color_before, color_trans, graph);
            trans_color(x, y-1, color_before, color_trans, graph);
        }
    }
}

void create_graph(int* graph){
    //随机给像素点赋值
    srand(time(NULL));
    for (int i=0; i < WIDTH; i++){
        for (int j=0; j < HEIGHT; j++){
            *(graph + i*HEIGHT + j) = random;
        }
    }
}

void show_graph(int* graph){
    for (int i=0; i < WIDTH; i++){
        for (int j=0; j < HEIGHT; j++){
            printf("%d ", *(graph + i*HEIGHT + j));
        }
        printf("\n");
    }
}
