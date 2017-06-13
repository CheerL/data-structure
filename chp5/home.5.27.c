#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define TYPE int

typedef struct OLNode
{
    int i, j;
    TYPE e;
    struct OLNode *right, *down;
} OLNode, *OLink;

typedef struct CrossList
{
    OLink *rhead, *chead;
    int mu, nu, tu;
} CrossList;

void matrix_plus(CrossList *M_A, CrossList *M_B);
void create_node(OLNode *node, int i, int j, TYPE e);
void create_martix(CrossList *M, int mu, int nu);
void generate_random_matrix(CrossList *M, int tu);
void insert_ele(CrossList *M, int i, int j, TYPE e);
void show_matrix(CrossList *M);
void show_zero(int num);
int random(int range);

int main()
{
    int width = 6;
    int height = 6;
    CrossList M_A, M_B;
    create_martix(&M_A, width, height);
    create_martix(&M_B, width, height);

    generate_random_matrix(&M_A, 8);
    generate_random_matrix(&M_B, 5);
    printf("matrix A:\n");
    show_matrix(&M_A);
    printf("matrix B:\n");
    show_matrix(&M_B);

    matrix_plus(&M_A, &M_B);
    printf("matrix A + matrix B:\n");
    show_matrix(&M_A);
    return 0;
}

void matrix_plus(CrossList *M_A, CrossList *M_B)
{
    if (!(M_A->mu == M_B->mu && M_A->nu == M_A->nu))
    {
        exit(-1);
    }
    for (int i = 0; i < M_B->mu; i++)
    {
        OLNode *p = M_B->rhead[i];
        while (p)
        {
            insert_ele(M_A, p->i, p->j, p->e);
            p = p->right;
        }
    }
}
void create_node(OLNode *node, int i, int j, TYPE e)
{
    node->i = i;
    node->j = j;
    node->e = e;
    node->right = NULL;
    node->down = NULL;
}

void create_martix(CrossList *M, int mu, int nu)
{
    if (M)
    {
        free(M);
    }
    M->mu = mu;
    M->nu = nu;
    M->tu = 0;
    M->rhead = (OLink *)malloc((M->mu) * sizeof(OLink));
    M->chead = (OLink *)malloc((M->nu) * sizeof(OLink));
    if (!M->rhead || !M->chead)
    {
        exit(-1);
    }
    for (int i = 0; i < M->mu; i++)
    {
        M->rhead[i] = NULL;
    }
    for (int i = 0; i < M->nu; i++)
    {
        M->chead[i] = NULL;
    }
}

void insert_ele(CrossList *M, int i, int j, TYPE e)
{
    if (!(M && i < M->mu && j < M->nu))
    {
        exit(-1);
    }
    OLNode *p = (OLNode *)malloc(sizeof(OLNode));
    create_node(p, i, j, e);
    if (M->rhead[i] == NULL || M->rhead[i]->j > j)
    {
        M->tu++;
        p->right = M->rhead[i];
        M->rhead[i] = p;
    }
    else
    {
        OLNode *q = M->rhead[i];
        while (q)
        {
            if (q->j == j)
            {
                q->e += e;
                break;
            }
            else if (!q->right)
            {
                M->tu++;
                q->right = p;
                break;
            }
            else if (q->j < j && q->right->j > j)
            {
                M->tu++;
                p->right = q->right;
                q->right = p;
                break;
            }
            else
            {
                q = q->right;
            }
        }
    }
    if (M->chead[j] == NULL || M->chead[j]->i > i)
    {
        p->down = M->chead[j];
        M->chead[j] = p;
    }
    else
    {
        OLNode *q = M->chead[j];
        while (q)
        {
            if (q->i == i)
            {
                break;
            }
            else if (!q->down)
            {
                q->down = p;
                break;
            }
            else if (q->i < i && q->down->i > i)
            {
                p->down = q->down;
                q->down = p;
                break;
            }
            else
            {
                q = q->down;
            }
        }
    }
}

void show_matrix(CrossList *M)
{
    for (int i = 0; i < M->mu; i++)
    {
        OLNode *p = M->rhead[i];
        if (!p)
        {
            show_zero(M->nu);
        }
        else
        {
            show_zero(p->j);
            while (p)
            {
                printf("%d\t", p->e);
                if (p->right)
                {
                    show_zero(p->right->j - p->j - 1);
                }
                else
                {
                    show_zero(M->nu - p->j - 1);
                }
                p = p->right;
            }
        }
        printf("\n");
    }
}

void show_zero(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("0\t");
    }
}

void generate_random_matrix(CrossList *M, int tu)
{
    struct timeval _time;
    gettimeofday(&_time, NULL);
    srand((unsigned)(_time.tv_sec * _time.tv_usec));
    usleep(1);
    for (int i = 0; i < tu; i++)
    {
        insert_ele(M, random(M->mu), random(M->nu), random(10) + 1);
    }
}

int random(int range)
{
    return rand() % range;
}