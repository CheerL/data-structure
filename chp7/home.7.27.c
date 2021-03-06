#include <stdio.h>
#include <stdlib.h>
#include "ALGraph.h"

VNode *empty_path(ALGraph G) // 返回一个空节点列表, 长度为G.vexnum
{
    VNode *path = (VNode *)malloc(G.vexnum * sizeof(VNode));
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
    {
        path[i].firstarc = NULL;
        path[i].data = NULL;
    }
    return path;
}

/********************************************
Function name:  find_path
Purpose:        寻找在图G中, 从点v到点w的路径
Params:
    @ALGraph    G:  给定的图
    @VNode      v:  起点
    @VNode      w:  终点
    @int        k:  目标路径长度
Return:         VNode*
    返回的是一个VNode节点的列表, 长度为G.vexnum
    若不存在路径          列表每一个元素都为空
    若存在路径           列表逆序给出了路径, 
                        即若路径为 v->a->b->c->w
                        返回列表 [w,c,b,a,v]
********************************************/
VNode *find_k_path(ALGraph G, VNode v, VNode w, int k)
{
    ArcNode *arc = v.firstarc;
    VNode *path = empty_path(G);
    if (!arc || k <= 0 || k > G.vexnum) // 若v没有相邻边, 或目标路径长为0, 或目标路径长大于图G中点的个数
    {                                   // 返回一个空列表
        return path;
    }

    while (arc) // 循环访问v的所有边
    {
        VNode arc_to = G.verteces[arc->adjvex]; // 找到当前边对应的点
        if (arc_to.data == w.data && k == 1)    // 若对应的点是目标点, 且目标路径长度为1
        {                                       // 将当前点放入列表并返回
            path[0] = w;
            path[1] = v;
            break;
        }
        else
        {
            path = find_k_path(G, arc_to, w, k - 1); // 递归访问当前边所指的点
            if (path[0].data)                        // 若返回的列表不是空的, 检查当前点是否曾出现
            {
                for (int i = 0; i < MAX_VERTEX_NUM; i++)
                {
                    if (path[i].firstarc == v.firstarc && path[i].data == v.data) // 若曾出现, 清空列表
                    {
                        path = empty_path(G);
                        break;
                    }
                    else if (path[i].firstarc == NULL && path[i].data == NULL) // 不曾出现, 将当前点插到列表最后
                    {
                        path[i] = v;
                        return path;
                    }
                }
            }

            arc = arc->nextarc; // 访问和当前点相邻的下一条边
        }
    }
    return path;
}