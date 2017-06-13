#define MAX_VERTEX_NUM 20
#define INFO_TYPE char
#define VERTEX_TYPE char

typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
    INFO_TYPE *info;
} ArcNode;

typedef struct VNode
{
    VERTEX_TYPE *data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct ALGraph
{
    AdjList verteces;
    int vexnum, arcnum;
    int kind;
} ALGraph;