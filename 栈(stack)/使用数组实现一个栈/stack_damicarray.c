#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 5
// top记录数组的下标；
bool isEmpty(int *top);
void Push(int **array, int x, int *top)
{
    if (*top == MAX_SIZE - 1) // MAX_SIZE - 1到达数组最后一个位置
    {
        // 需要扩展数组
        int *newArray = (int *)realloc(*array, sizeof(**array) * MAX_SIZE * 2);
        if (newArray == NULL)
        {
            printf("Memory allocation failed\n");
            free(*array); // 这里也可以不释放原数组，由主函数决定是否释放；
            return;
        }
        // 复制原数组内容到新数组
        // free(*array); 不能再释放原数组
        *array = newArray;
        printf("数组已经扩展\n");
        printf("Array resized to %d\n", MAX_SIZE * 2);
    }
    // top++;
    // A[top] = x
    (*array)[++(*top)] = x; // top先加1， 在A[top]赋值x
}
void Pop(int *top)
{                     // 判断数组是否为空
    if (isEmpty(top)) // top就是一个地址
    {
        printf("Error: No element to pop!\n");
        return;
    }
    (*top)--;
}
int Pop2(int *array, int *top)
{                     // 判断数组是否为空
    if (isEmpty(top)) // top就是一个地址
    {
        printf("Error: No element to pop!\n");
        return -1;
    }
    (*top)--;
    return array[*top + 1];
}
int Top(int *array, int *top)
{
    return array[*top];
}
bool isEmpty(int *top)
{
    // if (*top == -1)
    //     return true;
    // return false;
    return (*top == -1);
}
void Print(int *array, int *top)
{
    printf("stack: \n");
    for (int i = 0; i <= *top; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main()
{
    int top = -1; // top为-1表示数据为空
    int *array = (int *)malloc(sizeof(*array) * MAX_SIZE);
    if (array == NULL)
    {
        printf("Memory allocation failed\n");
        return 1; // 返回非零值表示错误
    }
    Push(&array, 2, &top);
    Print(array, &top);
    Push(&array, 3, &top);
    Print(array, &top);
    Push(&array, 4, &top);
    Print(array, &top);
    Push(&array, 5, &top);
    Print(array, &top);
    Push(&array, 6, &top);
    Print(array, &top);
    printf("--------------\n");
    Push(&array, 10, &top);
    Print(array, &top);
    printf("%d ", Top(array, &top));
    printf("\npop = %d ", Pop2(array, &top));
    Print(array, &top);

    free(array);  // 释放动态分配的内存
    array = NULL; // 避免悬空指针
    return 0;
}