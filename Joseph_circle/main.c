#include <conio.h>     // getch()
#include "circ_link.h" // 循环链表定义

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
void init();           // 初始化
void read_command();   // 读取命令
void interprect();     // 处理命令
                       //
void show_command();   // 显示命令提示
void show_info();      // 显示程序信息
                       //
void add_new_player(); // p 加入新玩家
void set_bound();      // b 设置报数上限
void number_off();     // n 依次报数并出列, 直至空列表, 输出出列顺序
void show();           // s 显示链表信息
void help();           // h 显示帮助信息

/* 全局变量声明 */
List L;
int number_bound;
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
void init()
{
    init_list(&L);
    set_bound();

    int n;
    printf("Please input the number of players: "); // 设定参与人数
    scanf("%d", &n);                                //
    if (n > 0)
    {
        for (int i = 0; i < n; i++) // 输入每个人的密码
        {
            add_new_player();
        }
    }
}

void show_info()
{
    CLEAR;
    LONG_STAR(80);
    printf("\n");
    printf("Joseph Circle\n");
    printf("\n");
    LONG_STAR(80);
    printf("\n\n");
}
void show_command()
{
    printf("\n\n");
    LONG_STAR(80);
    printf("\n");
    printf("Command:\tS(how)\t\tN(umber off)\tP(layer)\tB(ound)\n");
    printf("\t\tH(elp)\t\tQ(uit)\t\tR(erun)\n");
    printf("\n");
    LONG_STAR(80);
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
    case 'p':
        show_info();
        add_new_player();
        show_command();
        break;
    case 'b':
        show_info();
        set_bound();
        show_command();
        break;
    case 'r':
        show_info();
        init();
        show_command();
        break;
    case 'n':
        show_info();
        number_off();
        show_command();
        break;
    case 'h':
        show_info();
        help();
        show_command();
        break;
    }
}

void set_bound()
{
    printf("Please input the upper bound of numbering off: "); // 设定报数上限
    scanf("%d", &number_bound);
}

void add_new_player()
{
    int password;
    Type data;
    printf("Please input the password of player %d: ", L.size + 1);
    scanf("%d", &password);
    data.password = password;
    data.count = L.size + 1;
    insert_node(&L, data);
}

void number_off()
{
    Type data;
    goto_next_n_node(&L, 1);                        // 调整列表, 使当前节点指向第一个人
    printf("The order of player numbering off:\n"); //
    while (!is_empty(L))                            // 依次报数并出列直至队列为空, 输出出列顺序
    {
        goto_next_n_node(&L, number_bound - 1);
        data = get_data(L);
        printf("%d", data.count);
        number_bound = data.password;
        delete_node(&L);
    }
}

void show()
{
    if (L.size <= 0)
    {
        printf("There is no player.\n");
        return;
    }
    printf("Number of player:\t%d\n", L.size);
    printf("Bound of numbering off:\t%d\n", number_bound);
    printf("\n");
    printf("Player List:\n");
    for (int i = 0; i < L.size; i++)
    {
        printf("Player %d,  password %d\n", L.p->data.count, L.p->data.password);
        L.p = L.p->next;
    }
    // L.p = L.p->next;
}

void help()
{
    printf("Command list:\n\n");
    printf("h:\thelp\t\tGet command list.\n");
    printf("r:\trerun\t\tRerun the program.\n");
    printf("p:\tplayer\t\tAdd new player.\n");
    printf("n:\tnumber\t\tEach player numbers off and leaves queue, output the order.\n");
    printf("b:\tbound\t\tSet initial upper bound of numbering.\n");
    printf("s:\tshow\t\tShow the graph.\n");
    printf("q:\tquit\t\tQuit the program.\n");
}