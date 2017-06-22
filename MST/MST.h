#ifndef __WGRAPH__
#include "WGraph.h"
#endif

/********************************************
Function name:  get_MST
Purpose:        用Kruskal算法, 求所给图的最小生成树
Params:
    @WGraph     *G:         要加点的图
Return:         Status
    SUCCESS:    操作成功
    FAIL:       不存在最小生成树
********************************************/
Status get_MST(WGraph *G)
{
    /* 声明及初始化变量 */
    MFSet S;                      // MF集合用于保存当前的连通分支, 每一个子集都是G的一个连通分支
    initial_by_set(&S, G->vexs);  // 初始化MF集合
    edges_heap_sort(G);           // 对图G的边从小到大排序
                                  //
    int count = 0;                // 最小生成树(当前的)边数
    int m, n;                     //
    Edge edge;                    //
    Edge edge_list[MAX_EDGE_NUM]; // 最小生成树(当前的)所有边

    /* 算法主体 */
    for (int i = 0; i < G->edgenum && count < G->vexnum; i++) // 从最小权边开始, 遍历所有边
    {
        edge = G->edges[i];                        // 对于当前边edge
        m = find(S, edge.start);                   // 获取起点所在连通分支
        n = find(S, edge.end);                     // 获取终点所在连通分支
        if (m != -1 && n != -1 && m != n)          // 若两连通分支存在且不是同一个
        {                                          //
            merge(&S, m, n);                       // 合并这两个分支
            edge_equal(&edge_list[count++], edge); // 把这条边edge加到生成树的边中
        }
    }

    /* 结果判断与输出 */
    for (int k = 0; k < G->vexnum; k++)                       // 检查MF集合S
    {                                                         //
        if (S.set[k].size == G->vexnum)                       // 若存在一个子集, 包含了图G的所有点
        {                                                     //
            printf("The MST of this graph is as follows.\n"); // 那么算法得到的就是最小生成树, 输出
            for (int i = 0; i < G->vexnum - 1; i++)
            {
                edge = edge_list[i];
                printf("Edge: %d---%d, weight:%d\n", edge.start, edge.end, edge.weight);
            }
            return SUCCESS;
        }
    }
    printf("This graph is not connected, so there is no MST.\n"); // 否则说明图G有超过一个连通分支, 不存在MST
    return FAIL;
}