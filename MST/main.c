#include <conio.h>  // getch()
#include "MFSet.h"  // MFSet结构体及其操作
#include "WGraph.h" // 带权边数组储存的图结构体及其操作
#include "MST.h"    // 最小生成树算法

/* 宏定义操作函数 */

// 清屏
#ifdef WIN32
#define CLEAR system("cls")
#else
#define CLEAR system("clear")
#endif
// 打印长条的星星
#define LONG_STAR(num)            \
    for (int i = 0; i < num; i++) \
        printf("*");              \
    printf("\n");

/* 操作函数声明 */
void init();                 // 初始化
void read_command();         // 读取命令
void interprect();           // 处理命令
                             //
void show_command();         // 显示命令提示
void show_info();            // 显示程序信息
                             //
void add_new_vex();          // v 向图中加入新点
void add_new_edge(int help); // e 向图中加入新边
void show();                 // s 显示图的信息
void clear_graph();          // c 清理图使其为空图
void help();                 // h 显示帮助信息
//void get_MST();            // m 求最小生成树

/* 全局变量声明 */
WGraph G;
char cmd;

/* 主函数 */
int main()
{
    show_info();
    init();
    show_command();
    do
    {
        read_command();
        interprect();
    } while (cmd != 'q');
    return 0;
}

/* 操作函数定义 */
void show_info()
{
    CLEAR;
    LONG_STAR(100);
    printf("\n");
    printf("Minimun Spanning Tree\n");
    printf("\n");
    LONG_STAR(100);
    printf("\n\n");
}
void show_command()
{
    printf("\n\n");
    LONG_STAR(100);
    printf("\n");
    printf("Command:\tS(how)\t\tM(ST)\t\tE(dge)\t\tV(ex)\n");
    printf("\t\tH(elp)\t\tQ(uit)\t\tC(lear)\t\tR(erun)\n");
    printf("\n");
    LONG_STAR(100);
}

void init()
{
    init_graph(&G);
    int vexnum, edgenum;
    printf("Please input the number of verteces:");
    scanf("%d", &vexnum);
    for (int i = 0; i < vexnum; i++)
    {
        add_vertex(&G, i);
    }

    printf("Please input the number of edges:");
    scanf("%d", &edgenum);
    if (edgenum)
    {
        printf("Please input each edge in form \"start_point, end_point, weight\".\n");
        printf("Example: 2,3,5  (which means this edge is from point 2 to point 3 with weight 5).\n");
        for (int i = 0; i < edgenum; i++)
        {
            printf("Edge %d:", i);
            add_new_edge(0);
        }
    }
}

void read_command()
{
    cmd = getch();
    if (cmd >= 'A' && cmd <= 'Z')
    {
        cmd += 'a' - 'A';
    }
}

void interprect()
{
    switch (cmd)
    {
    case 's':
        show_info();
        show();
        show_command();
        break;
    case 'e':
        show_info();
        add_new_edge(1);
        show_command();
        break;
    case 'v':
        show_info();
        add_new_vex();
        show_command();
        break;
    case 'c':
        show_info();
        clear_graph();
        show_command();
        break;
    case 'm':
        show_info();
        get_MST(&G);
        show_command();
        break;
    case 'r':
        show_info();
        init();
        show_command();
        break;
    case 'h':
        show_info();
        help();
        show_command();
        break;
    }
}

void add_new_vex()
{
    Type vertex;
    printf("Please input new vertex:");
    scanf("%d", &vertex);
    if (is_in_set(G.vexs, vertex))
    {
        printf("Vertex %d is in the graph.\n", vertex);
    }
    else
    {
        add_vertex(&G, vertex);
    }
}

void add_new_edge(int help)
{
    if (G.vexnum <= 0)
    {
        printf("There is no vertex in the graph,\nso you unable to add edge.\n");
        return;
    }
    if (help)
    {
        printf("Please input new edge in form \"start_point, end_point, weight\".\n");
        printf("Example: 2,3,5  (which means this edge is from point 2 to point 3 with weight 5).\n");
    }
    int weight, start, end;
    scanf("%d,%d,%d", &start, &end, &weight);
    if (add_edge(&G, weight, start, end) == FAIL)
    {
        printf("Please input again.\n");
        add_new_edge(0);
    }
}

void show()
{
    printf("Number of verteces:\t%d\n", G.vexnum);
    printf("Number of edges:\t%d\n", G.edgenum);
    printf("\n");
    printf("Vertex List:\n");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("Vex %d:\t%d\n", i, G.vexs.elem[i]);
    }
    printf("\n");
    printf("Edge List:\n");
    for (int i = 0; i < G.edgenum; i++)
    {
        printf("Edge %d:\t%d--%d\tweight:%d\n", i, G.edges[i].start, G.edges[i].end, G.edges[i].weight);
    }
}

void clear_graph()
{
    G.vexnum = G.edgenum = G.vexs.size = 0;
    show();
}

void help()
{
    printf("Command list:\n\n");
    printf("h:\thelp\t\tGet command list.\n");
    printf("r:\trerun\t\tRerun the program.\n");
    printf("e:\tedge\t\tAdd new edge to the graph.\n");
    printf("v:\tvertex\t\tAdd new vertex to the graph.\n");
    printf("c:\tclear\t\tClear up the graph, make it empty.\n");
    printf("m:\tMST\t\tGet the MST of the graph.\n");
    printf("s:\tshow\t\tShow the graph.\n");
    printf("q:\tquit\t\tQuit the program.\n");
}