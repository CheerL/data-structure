#include <stdio.h>
#include <stdlib.h>
#include "ALGraph.h"

/********************************************
Function name:  find_source
Purpose:        寻找在有向无圈图G中的唯一源点
Params:
    @ALGraph    G:  给定的图
Return:         int
    -1:         不存在唯一的源点
    其他整数:    源点在图G的点列表中的序号
********************************************/
int find_source(ALGraph G)
{
    int *list = (int *)malloc((G.vexnum + 1) * sizeof(int)); // 生成一个列表用于去重, 列表长为G.vexnum + 1
    list[0] = G.vexnum;                                      // 第一个元素是当前剩下的点的个数
    for (int i = 0; i < G.vexnum; i++)                       // 访问过的点标记为0, 没访问过的点标记为1
    {
        list[i + 1] = 1;
    }

    for (int i = 0; i < G.vexnum; i++) // 循环访问G的所有点
    {
        ArcNode *arc = G.verteces[i].firstarc;
        while (arc)                         // 访问当前点的所有边
        {                                   // 判断该边所连的点
            if (list[arc->adjvex + 1] != 0) // 若前面没有访问过, 把改点标记为1
            {
                list[arc->adjvex + 1] = 0;
                list[0]--;
            }
            arc = arc->nextarc;
        }
    }

    if (list[0] == 1) // 若只剩一个点没有访问过, 找出这个点, 即源点
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            if (list[i + 1] != 0)
            {
                return i;
            }
        }
    }
    else // 超过1个点, 则源点不唯一, 返回0
    {
        return -1;
    }
}

/********************************************
Function name:  __print_expression_node
Purpose:        打印给定图G的以节点v为源的子图对应的表达式
                该函数只能被print_expression调用或者自身递归调用
Params:
    @ALGraph    G:  给定的图
    @VNode      v:  子图的源节点v
Return:         void
********************************************/
void __print_expression_node(ALGraph G, VNode v)
{
    ArcNode *arc = v.firstarc;
    while (arc) // 访问和v点相连的边arc
    {           // 递归打印以边arc所连的点为源点的子图对应的表达式
        __print_expression_node(G, G.verteces[arc->adjvex]);
        arc = arc->nextarc;
    }
    printf("%s", v.data); // 打印节点v对应的内容
}

/********************************************
Function name:  print_expression
Purpose:        打印给定图G对应的表达式
Params:
    @ALGraph    G:  给定的图
Return:         void
    当G不存在唯一的源点的时候, 会打印出错误警报
********************************************/
void print_expression(ALGraph G)
{
    int source = find_source(G); // 寻找G的唯一源点
    if (source == -1)            // 若不存在. 警报, 并结束
    {
        printf("所给的图不存在唯一的源点, 无法输出");
        return;
    }
    __print_expression_node(G, G.verteces[source]);
}