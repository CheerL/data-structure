//本段代码没有写相应结构, 不能运行
//仅写出流程
#define max(a, b) ((a > b) ? a : b)

int GListDepth(GList L)
{
    if (!L)
    {
        return 1; //空表深度为1
    }
    else if (L->tag == ATOM)
    {
        return 0; //原子深度为0
    }
    else
    {
        return max(GListDepth(L->hp) + 1, GListDepth(L->tp));
        //表头深度+1 和 表尾深度 中较大的那个即该表深度
    }
}