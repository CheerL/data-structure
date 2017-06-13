#include <stdlib.h>

#define MAXSIZE 20
#define KEY int
#define TYPE int

typedef struct Node
{
    KEY key;
    TYPE data;
} Node;

typedef struct List
{
    Node r[MAXSIZE];
    int len;
} List;

void node_swap(Node *a, Node *b)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    *temp = *a;
    *a = *b;
    *b = *temp;
}