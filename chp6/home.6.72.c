//本段代码没有实现相应结构, 不能运行

/********************************************
Function name:  traverse_print
Purpose:        按题中指定方式打印以孩子链储存的树
                此函数供外部调用
Params:
    @CTree      T:       需要打印的树
Return:         void
********************************************/
void traverse_print(CTree T)
{
    CTBox root = T.nodes[T.r];
    __traverse_print(T, root, 0);
}

/********************************************
Function name:  __traverse_print
Purpose:        按题中指定方式打印以孩子链储存的树
                此函数只能由traverse_print调用和自身递归调用
                函数主体采用递归的方式运行
Params:
    @CTree      T:      需要打印的原始的树
    @CTBox      box:    当前访问的节点
    @int        level   当前访问节点在原始的树中的层数(记原树根节点层数为0)
                        用于控制打印的制表符数量
Return:         void
********************************************/
void __traverse_print(CTree T, CTBox box, int level)
{
    if (box.data) // 节点非空
    {
        for (int i = 0; i < level; i++) // 打印当前节点
        {
            printf("\t");
        }
        printf("%s\n", box.data);

        ChildPtr p = box.firstchild;
        while (p) // 递归访问所有孩子节点
        {
            __traverse_print(T, T.nodes[p->child], level + 1);
            p = p->next;
        }
    }
}
