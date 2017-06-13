#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TrieTree.h"

#define ORD(c) (int)c - 'a' // 字母在字母表中的顺序

/********************************************
Function name:  delete_trie
Purpose:        将关键词word从Trie树T删除, 最大深度为max_depth
                默认所有word是由小写字母组成的
Params:
    @TrieTree   T:          要删除的TrieTree
    @char       *word:      要删除的关键字, 必须为小写字母组成
    @int        max_depth:  设定的最大树深度
Return:         Status
    SUCCESS:    删除成功
    FAIL:       删除失败
********************************************/
Status delete_trie(TrieTree T, char *word, int max_depth)
{
    TrieNode *p = T;
    for (int i = 0; i < max_depth && i < strlen(word); i++) // 循环word的每一个字符
    {                                                       // 直到超过最大深度或遍历完word
        if (p && p->kind == BRANCH)                         // 若节点非空, 且是分支节点
        {                                                   //
            TrieNode *next = p->bh.ptr[ORD(word[i])];       // 给出下一个对应节点
            if (next && next->kind == BRANCH)               // 若对应的下一个节点非空且是分支节点
            {                                               // 推进到下一个节点
                p = next;
            }
            else if (next && next->kind == LEAF)                     // 若对应的下一个非空且是叶子节点
            {                                                        //
                if (*(next->lf.info) == *word || i == max_depth - 2) // 若叶子的值就是word, 即找到目标节点
                {                                                    // 或是倒数第二层, 即找到了同义词节点
                    next = NULL;                                     // 删掉该节点
                    p->bh.num--;                                     // 并把上级分支节点计数减1
                    if (p->bh.num == 1)                              // 若上级分支节点p计数只剩1
                    {                                                // 尝试合并分支节点p
                        TrieNode *sub_node;                          //
                        for (int j = 0; j < 27; j++)                 // 遍历p找到唯一的子节点
                        {                                            //
                            sub_node = p->bh.ptr[j];                 //
                            if (sub_node)                            //
                                break;                               //
                        }                                            //
                        if (sub_node->kind == LEAF)                  // 若子节点是叶子, 合并, 否则不操作
                            p = sub_node;
                    }
                    return SUCCESS; // 删除成功
                }
                else // 没有找到要删除的点, 删除失败
                {
                    return FAIL;
                }
            }
            else // 当下一个节点是空的
            {    // 删除失败
                return FAIL;
            }
        }
        else // 若节点是空的或是叶子节点
        {    // 删除失败
            return FAIL;
        }
    }
    return FAIL; // 循环结束且没有返回值, 删除失败
}