//本段代码没有实现相应结构, 不能运行

// 用到的基本操作函数
void visit(BiTNode p);           // 访问节点p
void init_stack(Stack *S);       // 初始化栈
int empty_stack(Stack *S);       // 判断是否为空栈
void push(Stack *S, BiTNode *p); // 将节点p压入栈S
BiTNode *pop(Stack *S);          // 退栈, 获取栈顶节点p

/********************************************
Function name:  pre_order_traverse_by_stack
Purpose:        以栈的方式来先序遍历给定二叉树
Params:
    @BiTree     *T:         需要遍历的二叉树指针
    @void       *visit :    访问节点的操作函数(指针)
Return:         void
********************************************/
void pre_order_traverse_by_stack(BiTree *T, void (*visit)(BiTNode p))
{
    BiTNode *p;
    Stack S;
    init_stack(&S);
    push(&S, T);
    p = T;
    while (p)
    {
        visit(*p);          // 访问节点
        if (p->right_child) // 若有右子树, 压入栈
        {
            push(&S, p->right_child);
        }
        if (p->left_child) // 若有左子树, 访问左子树
        {
            p = p->left_child;
        }
        else // 若无左子树
        {
            if (!empty_stack(&S)) // 若栈非空, 退栈, 访问栈顶元素
            {
                p = pop(&S);
            }
            else // 若栈空, 结束遍历
            {
                return;
            }
        }
    }
}
