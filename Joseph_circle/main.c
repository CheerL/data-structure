#include "circ_link.h"

int main()
{
    List L = list_create();                         // 创建链表
    int n, m, password;                             // 声明变量
    Type data;                                      //
    printf("Please input the upper bound: ");       // 设定报数上限
    scanf("%d", &m);                                //
    printf("Please input the number of players: "); // 设定参与人数
    scanf("%d", &n);                                //
                                                    //
    for (int i = 0; i < n; i++)                     // 输入每个人的密码
    {
        printf("Please input the password of player %d: ", i + 1);
        scanf("%d", &password);
        data.password = password;
        data.count = i + 1;
        insert_node(&L, data);
    }
    goto_next_n_node(&L, 1);                  // 调整列表, 使当前节点指向第一个人
    printf("The order of player leaving:\n"); //
    while (!is_empty(L))                      // 依次出列直至队列为空, 输出出列顺序
    {
        goto_next_n_node(&L, m - 1);
        data = get_data(L);
        printf("%d", data.count);
        m = data.password;
        delete_node(&L);
    }
    return 0;
}