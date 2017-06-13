// 以下仅给出无向图的算法
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define INFO_TYPE char
#define VERTEX_TYPE char

typedef struct ArcCell
{
    int adj;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct Vertex
{
    VERTEX_TYPE *data;
    int num;
} Vertex, VertexList[MAX_VERTEX_NUM];

typedef struct MGraph
{
    VertexList vexs;
    AdjMatrix arcs;
    int vexnum, arcnum;
} MGraph;

void insert_vertex(MGraph G, Vertex v)
{
    G.vexnum++;
    v.num = G.vexnum;
    G.vexs[G.vexnum] = v;
    for (int i = 0; i < G.vexnum; i++)
    {
        G.arcs[G.vexnum][i].adj = 0;
        G.arcs[i][G.vexnum].adj = 0;
    }
}

void insert_arc(MGraph G, Vertex v, Vertex w)
{
    if (G.arcs[v.num][w.num].adj == 0 && G.arcs[w.num][v.num].adj == 0)
    {
        G.arcnum++;
        G.arcs[v.num][w.num].adj = 1;
        G.arcs[w.num][v.num].adj = 1;
    }
}

void delete_vex(MGraph G, Vertex v)
{
    if (v.data == G.vexs[v.num].data && v.num == G.vexs[v.num].num)
    {
        G.vexnum--;
        for (int i = v.num; i < G.vexnum; i++)
        {
            G.vexs[i].data = G.vexs[i + 1].data;
            G.vexs[i].num = i;
        }
        for (int i = 0; i < G.vexnum + 1; i++)
        {
            if (G.arcs[v.num][i].adj == 1 && G.arcs[i][v.num].adj == 1)
            {
                G.arcnum--;
            }
        }
        for (int i = v.num; i < G.vexnum; i++)
        {
            for (int j = 0; j < G.vexnum; j++)
            {
                G.arcs[i][j].adj = G.arcs[i + 1][j].adj;
                G.arcs[j][i].adj = G.arcs[j][i + 1].adj;
            }
        }
    }
}

void delete_arc(MGraph G, Vertex v, Vertex w)
{
    if (G.arcs[v.num][w.num].adj == 1 && G.arcs[w.num][v.num].adj == 1)
    {
        G.arcnum--;
        G.arcs[v.num][w.num].adj = 0;
        G.arcs[w.num][v.num].adj = 0;
    }
}