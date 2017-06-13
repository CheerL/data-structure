//本段代码没有实现相应结构, 不能运行

void switch_left_and_right(BiTree *T)
{
    if (!T)
    {
        return;
    }

    BiTNode *temp;
    temp = T->left_child;
    T->lefr_child = T->right_child;
    T->right_child = temp;

    switch_left_and_right(T->left_child);
    switch_left_and_right(T->right_child);
}