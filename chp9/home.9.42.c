#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TrieTree.h"

#define ORD(c) (int)c - 'a' // 字母在字母表中的顺序

/********************************************
Function name:  insert_trie
Purpose:        将关键词word插入Trie树T, 最大深度为max_depth
                默认所有word是由小写字母组成的
Params:
    @TrieTree   T:          要插入的TrieTree
    @char       *word:      要插入的关键字, 必须为小写字母组成
    @int        max_depth:  设定的最大树深度
Return:         Status
    SUCCESS:    插入成功
    FAIL:       插入失败
********************************************/
Status insert_trie(TrieTree T, char *word, int max_depth)
{
    TrieNode *p = T;
    for (int i = 0; i < max_depth && i < strlen(word); i++) // 循环word的每一个字符
    {                                                       // 直到超过最大深度或遍历完word
        if (p && p->kind == BRANCH)                         // 若节点非空, 且是分支节点
        {                                                   //
            if (p->bh.ptr[ORD(word[i])])                    // 当对应的下一个节点非空
            {                                               // 推进到下一个节点
                p = p->bh.ptr[ORD(word[i])];
            }
            else // 当下一个节点是空的
            {    // 将word存入叶子节点, 并插入
                TrieNode *temp_lf = (TrieNode *)malloc(sizeof(TrieNode));
                temp_lf->kind = LEAF;
                temp_lf->lf.info = word;
                p->bh.ptr[ORD(word[i])] = temp_lf;
                p->bh.num++;
            }
        }
        else if (p && p->kind == LEAF)                        // 当前节点非空且是叶子节点
        {                                                     //
            if (*(p->lf.info) == *word || i == max_depth - 1) // 若节点的值就是word值, 无序插入
            {                                                 // 或最大已经达到最大深度, 当前词被作为同义词
                return SUCCESS;                               // 返回成功
            }                                                 //
            else                                              // 若节点不是word值, 且未达最大深度
            {                                                 // 分裂叶子节点为分支节点, 并插入新叶子
                TrieNode *temp_lf = (TrieNode *)malloc(sizeof(TrieNode));
                temp_lf->kind = LEAF;
                temp_lf->lf.info = word;

                TrieNode *temp_bh = (TrieNode *)malloc(sizeof(TrieNode));
                temp_bh->kind = BRANCH;
                temp_bh->bh.ptr[ORD(p->lf.info[i])] = p;
                temp_bh->bh.ptr[ORD(word[i])] = temp_lf;
                p = temp_bh;
                return SUCCESS;
            }
        }
        else // 若节点是空的
        {    // 插入失败
            return FAIL;
        }
    }
    return FAIL; // 循环结束且没有返回值, 插入失败
}