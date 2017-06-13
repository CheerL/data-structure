#ifndef TYPE
#define TYPE int
#endif

typedef struct BiTNode
{
    TYPE data;
    BiTNode *left_child, *right_child;
} BiTNode, *BiTree;