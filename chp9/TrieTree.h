#ifndef TYPE
#define TYPE char
#endif

typedef enum NodeKind {
    LEAF,
    BRANCH
} NodeKind;

typedef enum Status {
    FAIL = -1,
    SUCCESS = 0
} Status;

// 结构体前向声明
typedef struct TrieNode TrieNode;
typedef struct TrieNode
{
    NodeKind kind;
    union {
        struct
        {
            TYPE K;
            char *info;
        } lf;
        struct
        {
            TrieNode *ptr[27];
            int num;
        } bh;
    };
} TrieNode, *TrieTree;