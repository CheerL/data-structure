#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int reduce_sum(int count, int len, int *array);
int reduce_pro(int count, int len, int *array);
void generate_random_matrix(int *matrix_size, int *matrix, int order);
void loop(int count, int all, int order, int *matrix, int *matrix_size,
          int *exp_list);
void print_item(int *martix, int *matrix_size, int *exp_list, int order);

int ORDER = 3;
int MATRIX_SIZE[] = {5, 5, 5};
int IS_FIRST = 1;

int main()
{
    int matrix_total_size = reduce_pro(ORDER, ORDER, MATRIX_SIZE);
    int *matrix = (int *)malloc(sizeof(int) * matrix_total_size);
    int *exp_list = (int *)malloc(sizeof(int) * ORDER);
    generate_random_matrix(MATRIX_SIZE, matrix, ORDER);

    int max_all_exp = reduce_sum(ORDER, ORDER, MATRIX_SIZE) - ORDER;
    for (int i = max_all_exp; i >= 0; i--)
    {
        loop(0, i, ORDER, matrix, MATRIX_SIZE, exp_list);
    }
    return 0;
}

int reduce_sum(int count, int len, int *array)
{
    int sum = 0;
    for (int i = 0; i < fmin(len, count); i++)
    {
        sum += array[i];
    }
    return sum;
}
int reduce_pro(int count, int len, int *array)
{
    int pro = 1;
    for (int i = 0; i < fmin(len, count); i++)
    {
        pro *= array[i];
    }
    return pro;
}

void generate_random_matrix(int *matrix_size, int *matrix, int order)
{
    srand(time(NULL));
    for (int i = 0; i < reduce_pro(order, order, matrix_size); i++)
    {
        *(matrix + i) = rand() % 10;
    }
}

void loop(int count, int all, int order, int *matrix, int *matrix_size,
          int *exp_list)
{
    int all_left = all - reduce_sum(count, order, exp_list);
    if (count == order - 1)
    {
        if (all_left < matrix_size[count])
        {
            exp_list[count] = all_left;
            print_item(matrix, matrix_size, exp_list, order);
        }
    }
    else
    {
        for (int i = fmin(all_left, matrix_size[count] - 1); i >= 0; i--)
        {
            exp_list[count] = i;
            loop(count + 1, all, order, matrix, matrix_size, exp_list);
        }
    }
    return;
}

void print_item(int *matrix, int *matrix_size, int *exp_list, int order)
{
    int offsets = 0;
    for (int i = 0; i < order; i++)
    {
        offsets += (exp_list[i] * reduce_pro(i, order, matrix_size));
    }
    int coef = *(matrix + offsets);
    if (coef != 0)
    {
        if (!IS_FIRST)
        {
            printf("+");
        }
        else
        {
            IS_FIRST = 0;
        }
        if (coef != 1)
        {
            printf("%d", coef);
        }
    }
    for (int i = 0; i < order; i++)
    {
        int _exp = *(exp_list + i);
        if (_exp == 0)
        {
            continue;
        }
        else
        {
            printf("x_%d", i);
            if (_exp != 1)
            {
                printf("^%d", _exp);
            }
        }
    }
}
