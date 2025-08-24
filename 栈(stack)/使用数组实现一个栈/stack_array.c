#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 5
int A[MAX_SIZE];
// top记录数组的下标；
int top = -1; // top为-1表示数据为空
bool isEmpty();
void Push(int x)
{
    if (top == MAX_SIZE - 1) // MAX_SIZE - 1到达数组最后一个位置
    {

        printf("Error: stack overflow\n"); // 打印错误信息
        return;
    }
    // top++;
    // A[top] = x
    A[++top] = x; // top先加1， 在A[top]赋值x
}
void Pop()
{ // 判断数组是否为空
    if (isEmpty())
    {
        printf("Error: No element to pop!\n");
        return;
    }
    top--;
}
int Top()
{
    return A[top]; // 返回栈顶元素
}
bool isEmpty()
{
    if (top == -1)
        return true;
    return false;
}
void Print()
{
    printf("stack: \n");
    for (int i = 0; i <= top; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}
int main()
{
    Push(2);
    Print();
    Push(5);
    Print();
    Push(10);
    Print();
    Pop();
    Print();
    Push(12);
    Print();
    Pop();
    Pop();
    Pop();
    Pop();

    Print();
    printf("top = %d\n", top);

    return 0;
}