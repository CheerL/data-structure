#include <stdio.h>
#include <stdarg.h> // 用于实现可变参数
#include <stdlib.h>

#define __MFSET__
#define MAX_SET_NUM 30
#define MAX_NUMBER 100
#define Type int

/* 结构体定义 */
typedef enum Status { // 操作状态
    FAIL = -1,
    SUCCESS = 0
} Status;

typedef struct Set          // 集合
{                           //
    int size;               // 集合元素个数
    Type elem[MAX_SET_NUM]; // 集合元素数组
} Set;

typedef struct MFSet      // MF集合
{                         //
    int size;             // 元素总个数
    Set set[MAX_SET_NUM]; // 子集数组
} MFSet;

/* 操作函数声明 */
Status initial(MFSet *S, int size, ...);  // 初始化MF集合
Status initial_by_set(MFSet *MFS, Set S); // 从给定集合初始化MF集合
int is_in_set(Set S, Type x);             // 判断元素是否在集合中
int find(MFSet S, Type x);                // 从MF集合中找出给定元素所在子集
Status merge(MFSet *S, int i, int j);     // 合并MF集合中的子集

/* 操作函数定义 */

/********************************************
Function name:  initial
Purpose:        初始化MF集合, 给定size个元素, 每个元素作为一个子集
Params:
    @MFSet      *S:     要初始化的MF集合
    @int        size:   MF集合元素总个数
    @Type       ...:    可变参数, 应输入size个, 作为S的元素
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status initial(MFSet *S, int size, ...)
{
    va_list elements;
    va_start(elements, size);
    Type elem;
    for (int i = 0; i < size; i++)
    {
        elem = va_arg(elements, Type);
        if (elem > MAX_NUMBER || elem < -MAX_NUMBER)
        {
            printf("Input data %d out of range [-%d, %d].\n", elem, MAX_NUMBER, MAX_NUMBER);
            return FAIL;
        }
        S->set[i].elem[0] = elem;
        S->set[i].size = 1;
    }
    S->size = size;
    va_end(elements);
    return SUCCESS;
}

/********************************************
Function name:  initial_by_set
Purpose:        由给定的集合S, 初始化MF集合MFS
                S集合中的每个元素, 都会成为MFS的一个子集
Params:
    @MFSet      *MFS:   要初始化的MF集合
    @Set        S:      用于给定元素的集合
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status initial_by_set(MFSet *MFS, Set S)
{
    Type elem;
    for (int i = 0; i < S.size; i++)
    {
        elem = S.elem[i];
        if (elem > MAX_NUMBER || elem < -MAX_NUMBER)
        {
            printf("Input data %d out of range [-%d, %d].\n", elem, MAX_NUMBER, MAX_NUMBER);
            return FAIL;
        }
        MFS->set[i].elem[0] = elem;
        MFS->set[i].size = 1;
    }
    MFS->size = S.size;
    return SUCCESS;
}

/********************************************
Function name:  find
Purpose:        寻找给定元素在MF集合所在的子集, 返回子集序号
Params:
    @MFSet      *S:     要查找的MF集合
    @Type       x:      给定的元素x
Return:         int
    -1:         x不在S中
    else:       x在S的第i个子集S.set[i]中
********************************************/
int find(MFSet S, Type x)
{
    for (int i = 0; i < S.size; i++)
    {
        if (is_in_set(S.set[i], x))
        {
            return i;
        }
    }
    return -1;
}

/********************************************
Function name:  merge
Purpose:        给定两个序号i,j, 合并MF集合中对应的子集
                后一个子集并入前一个, 后一个子集变成空集
Params:
    @MFSet      *S:     要查找的MF集合
    @int        i:      被并入的子集序号(合并成功后非空)
    @int        j:      并入的子集序号(合并成功后变成空集)
Return:         Status
    SUCCESS:    操作成功
    FAIL:       操作失败
********************************************/
Status merge(MFSet *S, int i, int j)
{
    if (i == j) // 若是同一个子集, 合并失败
    {
        printf("Given sets are the same set.\n");
        return FAIL;
    }
    else if (i < 0 || i > S->size || j < 0 || j > S->size) // 若某个集合不在S中, 合并失败
    {
        printf("One of the given sets is not in MFSet S.\n");
        return FAIL;
    }
    else if (S->set[i].size <= 0 || S->set[j].size <= 0) // 若某个子集我空的, 合并失败
    {
        printf("One of the given sets is empty.\n");
        return FAIL;
    }
    else // 正常合并
    {
        int flag = 1;
        for (int m = 0; m < S->set[j].size; m++)
        {
            for (int n = 0; n < S->set[i].size; n++)
            {
                if (S->set[i].elem[n] == S->set[j].elem[m])
                {
                    flag = 0;
                    break;
                }
            }

            if (flag)
            {
                if (S->set[i].size >= MAX_SET_NUM)
                {
                    printf("Set overflows.\n");
                    return FAIL;
                }
                S->set[i].elem[S->set[i].size++] = S->set[j].elem[m];
            }
            else
            {
                flag = 1;
            }
        }
    }
    S->set[j].size = 0;
    return SUCCESS;
}

/********************************************
Function name:  is_in_set
Purpose:        判断给定元素是否在集合中
Params:
    @Set        S:      要查找的集合
    @Type       x:      给定的元素
Return:         int
    1:          x在S中
    0:          x不在S中
********************************************/
int is_in_set(Set S, Type x)
{
    if (S.size > 0)
    {
        for (int j = 0; j < S.size; j++)
        {
            if (S.elem[j] == x)
            {
                return 1;
            }
        }
    }
    return 0;
}