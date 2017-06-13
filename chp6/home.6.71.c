//本段代码没有实现相应结构, 不能运行

/********************************************
Function name:  traverse_print
Purpose:        按题中指定方式打印以孩子-兄弟链储存的树
                此函数供外部调用
Params:
    @Tree       T:     需要打印的树
Return:         void
********************************************/
void traverse_print(Tree T)
{
    __traverse_print(T, 0);
}

/********************************************
Function name:  __traverse_print
Purpose:        按题中指定方式打印以孩子-兄弟链储存的树
                此函数只能由traverse_print调用和自身递归调用
                函数主体采用递归的方式运行
Params:
    @Tree       T:      需要打印的树
    @int        level   该子树的根节点在原始的树中的层数(记原树根节点层数为0)
                        用于控制打印的制表符数量
Return:         void
********************************************/
void __traverse_print(Tree T, int level)
{
    if (T)
    {
        for (int i = 0; i < level; i++) // 打印当前树的根节点
        {
            printf("\t");
        }
        printf("%s\n", T->data);

        __traverse_print(T->first_child, level + 1); // 递归访问第一个孩纸节点
        __traverse_print(T->first_sibling, level);   // 递归访问第一个兄弟节点
    }
}
