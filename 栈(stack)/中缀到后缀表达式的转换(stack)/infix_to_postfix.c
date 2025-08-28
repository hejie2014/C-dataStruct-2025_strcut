#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "malloc failed\n"); // 打印错误信息到标准错误
        exit(EXIT_FAILURE);                 // 异常退出
    }
    // 赋值
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void push(Node **top, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}
int pop(Node **top)
{
    Node *temp = *top;
    // if (*top == NULL)
    // {
    //     printf("The stack is empty! Cannot pop.\n");
    //     return -1;
    // }
    if (*top == NULL)
    {
        // 在括号匹配函数中，我们已经确保不会在空栈上pop，所以这里可以改为更严格的处理，比如退出程序
        fprintf(stderr, "pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    int value = temp->data;
    *top = (*top)->next;
    free(temp);
    return value;
}
int topValue(Node *top)
{
    if (top == NULL)
    {
        return '\0'; // 空栈，返回空字符
    }
    return top->data;
}
bool isEmpty(Node *top)
{
    return top == NULL;
}
void Print(Node *top)
{
    if (isEmpty(top))
    {
        printf("NULL\n");
        return;
    }
    Node *temp = top;
    while (temp != NULL)
    {
        printf("%c", temp->data);
        if (temp->next != NULL)
        {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}
// 释放链表
void freeList(Node **top)
{
    if (*top == NULL)
    {
        printf("the stack is empty!\n");
        return;
    }
    Node *temp = *top;
    while (*top != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
    *top = NULL; // 将指针设置为NULL
    printf("the memory has been released!\n");
}
// 判断操作符
bool isOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}
bool isNumericDigit(char c)
{
    return (c >= '0' && c <= '9');
}
bool hasHigherPrec(char top, char c)
{
    if (top == '*' || top == '/')
        return true;
    else if ((top == '+' || top == '-') && (c == '+' || c == '-'))
        return true;
    return false;
}
char *infixToPostfix(char *exp)
{
    Node *top = NULL;
    int number = strlen(exp);
    char *result = malloc(sizeof(char) * 64); // 转化后的表达式
    int count = 0;                            // result下标计数
    for (int i = 0; i < number; i++)
    {
        if (isNumericDigit(exp[i]))
        {
            result[count] = exp[i];
            count++;
        }
        else if (isOperator(exp[i]))
        {
            while (!isEmpty(top) && hasHigherPrec(topValue(top), exp[i]))
            {
                result[count] = pop(&top);
                count++;
            }
            push(&top, exp[i]);
        }
    }
    while (!isEmpty(top))
    {
        result[count] = pop(&top);
        count++;
    }
    result[count] = '\0';
    return result;
}

int main()
{
    Node *top = NULL;
    char exp[] = "2+3*4-5*6";
    char *res = infixToPostfix(exp);
    printf("res = %s", res);
    free(res);
    // printf("%d", hasHigherPrec('+', '-'));
    // printf("%d", hasHigherPrec('+', '+'));
    // printf("%d", hasHigherPrec('+', '*'));
    // printf("%d", hasHigherPrec('+', '/'));
    // printf("%d", hasHigherPrec('-', '-'));
    // printf("%d", hasHigherPrec('-', '+'));
    // printf("%d", hasHigherPrec('-', '*'));
    // pop(&top);
    // freeList(&top);
    // printf("value = %c", topValue(top));
    // push(&top, '(');
    // push(&top, '2');
    // push(&top, '+');
    // push(&top, '3');
    // push(&top, ')');
    // Print(top);
    // pop(&top);
    // Print(top);
    // freeList(&top);
    return 0;
}