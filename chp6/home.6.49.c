//本段代码没有实现相应结构, 不能运行

// 用到的基本操作函数
void init_queue(Queue *Q);           // 初始化队列
void get_head(Queue *Q, BiTNode *p); // 获取队首元素
void push(Queue *Q, BiTNode *p);     // 压入队尾
int empty_queue(Queue *Q);           // 判断是否为空队列

/********************************************
Function name:  is_complete_bitree
Purpose:        判断给定二叉树是否为完全二叉树, 利用队列
Params:
    @BiTree     T:  需要判断的二叉树
Return:         int
    0:          不是完全二叉树
    1:          是完全二叉树
********************************************/
int is_complete_bitree(BiTree *T)
{
    Queue Q;
    BiTNode *p;
    int flag = 0; // 是否遇到过非满节点
                  // 即只有左子树, 或只有右子树, 或叶子
    init_queue(&Q);
    push(&Q, T);
    while (!empty_queue(&Q)) // 层遍历, 循环至队列为空
    {
        p = get_head(&Q);
        if (p->left_child && p->right_child) // 若有左右子树
        {
            if (!flag) // 若没有遇到非满节点, 将左右子树压入队列
            {
                push(&Q, p->left_child);
                push(&Q, p->right_child);
            }
            else // 遇到过, 则说明树不是完全的
            {
                return 0;
            }
        }
        else if (p->left_child) // 只有左子树, 非满节点
        {
            if (!flag) // 若没有遇到非满节点, 左子树压入队列
            {
                push(&Q, p->left_child);
                flag = 1;
            }
            else // 遇到过, 则说明树不是完全的
            {
                return 0;
            }
        }
        else if (p->right_child) // 只有右子树, 则说明树不是完全的
        {
            return 0;
        }
        else // 叶子节点, 其后的所有节点必须都是叶子
        {
            flag = 1;
        }
    }
    return 1; // 遍历完成, 说明是完全的
}