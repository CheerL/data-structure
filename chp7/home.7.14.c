#include <stdio.h>
#include <stdlib.h>
#include "ALGraph.h"

int main()
{
    int vexnum, arcnum;
    ALGraph graph;
    printf("Please input verteces num:");
    scanf("%d", &vexnum);
    printf("Please input arcs num:");
    scanf("%d", &arcnum);
    graph.vexnum = vexnum;
    graph.arcnum = arcnum;
    for (int i = 0; i < graph.vexnum; i++)
    {
        char *temp_str = (char *)malloc(sizeof(char));
        printf("Please input data of vex %d:", i);
        scanf("%s", temp_str);
        graph.verteces[i].data = temp_str;
        graph.verteces[i].firstarc = NULL;
    }
    for (int i = 0; i < graph.arcnum; i++)
    {
        int from, to;
        char *temp_str = (char *)malloc(sizeof(char));
        printf("Please input info of arc %d:", i);
        scanf("%s", temp_str);
        printf("arc %d from:", i);
        scanf("%d", &from);
        printf("arc %d to:", i);
        scanf("%d", &to);
        ArcNode *arc = (ArcNode *)malloc(sizeof(ArcNode));
        arc->adjvex = to;
        arc->nextarc = NULL;
        arc->info = temp_str;

        if (!graph.verteces[from].firstarc)
        {
            graph.verteces[from].firstarc = arc;
        }
        else
        {
            ArcNode *n = graph.verteces[from].firstarc;
            while (n->nextarc)
            {
                n = n->nextarc;
            }
            n->nextarc = arc;
        }
    }
    return 0;
}