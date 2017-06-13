#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"

#define TYPE int // 默认节点元素类型为int

/********************************************
Function name:  print_bst
Purpose:        从大到小打印二叉查找树T中大于x的元素
Params:
    @BiTree     T:  要打印的树
    @TYPE       x:  要比较的元素
Return:         void
********************************************/
void print_bst(BiTree T, TYPE x)
{
    if (T->data)                          // 若节点非空, 进行打印操作, 否则直接退出
    {                                     //
        if (T->data == x)                 // 当节点元素和x相等
        {                                 //
            print_bst(T->right_child, x); // 先打印右树
            printf("%d", T->data);        // 再打印本身
            print_bst(T->left_child, x);  // 最后打印左树
        }
        else if (T->data < x)             // 当节点元素小于x
        {                                 // 所有想要的元素都在右树
            print_bst(T->right_child, x); // 打印右树
        }                                 //
        else                              // 当节点大于x
        {                                 // 所有想要的元素都在左树
            print_bst(T->left_child, x);  // 打印左树
        }
    }
}