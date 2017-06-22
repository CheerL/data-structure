#ifndef __MFSET__
#include "MFSet.h"
#endif

#define __WGRAPH__
#define MAX_EDGE_NUM 100
#define MAX_VEX_NUM 30
#define MAX_WEIGHT 100

/* 结构体定义 */
typedef struct Edge // 边
{                   //
    int weight;     // 边的权
    int start;      // 边的起点
    int end;        // 边的终点 (若是无向图, 起点终点可以互换)
} Edge;

typedef struct WGraph         // 带权图
{                             //
    int edgenum, vexnum;      // 边数, 点数
    Set vexs;                 // 点集
    Edge edges[MAX_EDGE_NUM]; // 边集(边的数组)
} WGraph;

/* 操作函数声明 */
Status init_graph(WGraph *G);                               // 初始化图, 边数点数为0
Status add_edge(WGraph *G, int weight, int start, int end); // 向图G中插入从start到end的, 权为weight的边
Status add_vertex(WGraph *G, Type vertex);                  // 向图G中插入编号为vertex的点
void edge_equal(Edge *edge_i, Edge edge_j);                 // 边赋值
Status edges_heap_sort(WGraph *G);                          // 将边集按权从小到大排序, 使用堆排序
void edge_heap_adjust(Edge *edges, int s, int m);           // 边集的堆排序中的调整函数

/* 操作函数定义 */

/********************************************
Function name:  init_graph
Purpose:        初始化给定图, 边数点数都归0
Params:
    @WGraph     *G:     要初始化的图
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status init_graph(WGraph *G)
{
    G->vexnum = G->edgenum = G->vexs.size = 0;
    return SUCCESS;
}

/********************************************
Function name:  add_edge
Purpose:        向图G中插入从start到end的, 权为weight的边, 同时边数加1
                若是无向图, 边的起点和终点可以互换
Params:
    @WGraph     *G:         要加边的图
    @int        weight:     边的权值
    @int        start:      边的起点
    @int        end:        边的终点
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status add_edge(WGraph *G, int weight, int start, int end)
{
    if (G->edgenum >= MAX_EDGE_NUM)
    {
        printf("The number of edges reachs maximun %d.\n", MAX_EDGE_NUM);
        return FAIL;
    }
    else if (weight > MAX_WEIGHT || weight <= 0)
    {
        printf("The edge's weight is out of range (0, %d].\n", MAX_WEIGHT);
        return FAIL;
    }
    else if (!is_in_set(G->vexs, start) || !is_in_set(G->vexs, end))
    {
        printf("The edge's point is not in the graph's vertex set.\n");
        return FAIL;
    }
    else
    {
        G->edges[G->edgenum].weight = weight;
        G->edges[G->edgenum].start = start;
        G->edges[G->edgenum].end = end;
        G->edgenum++;
        return SUCCESS;
    }
}

/********************************************
Function name:  add_vertex
Purpose:        向图G中加入点
Params:
    @WGraph     *G:         要加点的图
    @Type       vertex:     新加点的编号
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status add_vertex(WGraph *G, Type vertex)
{
    if (G->vexnum >= MAX_VEX_NUM)
    {
        printf("The number of vertex reachs maximun %d.\n", MAX_VEX_NUM);
        return FAIL;
    }
    else
    {
        if (!is_in_set(G->vexs, vertex))
        {
            G->vexs.elem[G->vexnum++] = vertex;
            G->vexs.size++;
            return SUCCESS;
        }
        else
        {
            printf("The vertex is in vertex set of the graph.\n");
            return FAIL;
        }
    }
}

/********************************************
Function name:  edge_equal
Purpose:        边赋值, 把edge_j的起点,终点和权值赋给edge_i
Params:
    @Edge       *edge_i:    被赋值的边(即等号左边的)
    @Edge       edge_j:     提供值的边(即等号右边的)
Return:         void
********************************************/
void edge_equal(Edge *edge_i, Edge edge_j)
{
    edge_i->weight = edge_j.weight;
    edge_i->start = edge_j.start;
    edge_i->end = edge_j.end;
}

/********************************************
Function name:  edges_heap_sort
Purpose:        将所给图的边集按权从小到大排序, 使用堆排序
Params:
    @WGraph     *G:       要排序的图
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status edges_heap_sort(WGraph *G)
{
    for (int i = G->edgenum / 2; i >= 0; i--)
    {
        edge_heap_adjust(G->edges, i, G->edgenum);
    }
    for (int i = G->edgenum; i >= 1; --i)
    {
        Edge temp;
        edge_equal(&temp, G->edges[0]);
        edge_equal(&G->edges[0], G->edges[i - 1]);
        edge_equal(&G->edges[i - 1], temp);
        edge_heap_adjust(G->edges, 0, i - 2);
    }
    return SUCCESS;
}

/********************************************
Function name:  edges_heap_sort
Purpose:        (边集)堆排序中的堆调整函数
Params:
    @Edge       *edges:     要排序的边集
    @int        s:          堆顶
    @int        m:          堆大小
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
void edge_heap_adjust(Edge *edges, int s, int m)
{
    Edge temp;
    edge_equal(&temp, edges[s]);
    for (int i = 2 * s; i < m; i *= 2)
    {
        if (i < m && edges[i].weight < edges[i + 1].weight)
        {
            ++i;
        }
        if (!(temp.weight < edges[i].weight))
        {
            break;
        }
        edge_equal(&(edges[s]), edges[i]);
        s = i;
    }
    edge_equal(&(edges[s]), temp);
}
