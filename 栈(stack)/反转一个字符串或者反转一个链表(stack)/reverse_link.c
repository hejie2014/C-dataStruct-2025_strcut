#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 将元素压入栈顶
void push(Node **top, int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    // 检查内存是否分配成功
    if (temp == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    temp->data = data;
    temp->next = NULL;
    temp->next = *top; // 新建节点指向top的节点
    *top = temp;       // 更新top指针
}
// 弹出栈顶元素
void pop(Node **top)
{
    Node *temp = *top;
    // 检查栈是否为空
    if (*top == NULL)
    {
        printf("the linkListed no element!\n");
        return;
    }
    *top = (*top)->next;
    free(temp);
}
// 获取栈顶元素的值
int topValue(Node *top)
{
    if (top == NULL)
    {
        printf("the linkListed no element!\n");
        return -1; // 返回一个错误码
    }
    return top->data;
}
// 检查栈是否为空
bool isEmpty(Node *top)
{
    return top == NULL;
}
// 打印栈的内容
void Print(Node *top)
{
    Node *temp = top;
    if (temp == NULL)
    {
        printf("NULL\n");
        return;
    }
    while (temp != NULL)
    {
        printf("%d", temp->data);
        if (temp->next != NULL)
        {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}
void freeList(Node **top)
{
    Node *temp = *top;
    while (*top != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
    *top = NULL; // 将指针设置为NULL
    printf("The memory has been released\n");
}

void reverse(Node **top)
{
    if (isEmpty(*top))
        return;
    Node *temp = NULL;
    Node *current = *top;
    while (current != NULL)
    {
        push(&temp, current->data);
        current = current->next;
    }
    freeList(top);
    *top = temp;
}

int main()
{
    Node *top = NULL; // 创建一个空栈

    // 测试空栈操作
    printf("Testing empty stack operations:\n");
    pop(&top);
    printf("Top value of empty stack: %d\n", topValue(top));
    printf("Is stack empty? %s\n", isEmpty(top) ? "Yes" : "No");
    printf("Stack contents: ");
    Print(top);
    printf("\n");

    // 测试压栈操作
    printf("Testing push operations:\n");
    push(&top, 1);
    Print(top);
    push(&top, 2);
    Print(top);
    push(&top, 4);
    Print(top);
    push(&top, 3);
    Print(top);
    push(&top, 8);
    Print(top);
    printf("\n");
    reverse(&top);
    Print(top);
    // // 测试栈顶和弹出操作
    // printf("Testing top and pop operations:\n");
    // printf("Top value: %d\n", topValue(top));
    // pop(&top);
    // Print(top);
    // printf("Top value: %d\n", topValue(top));
    // pop(&top);
    // Print(top);
    // printf("\n");

    // 释放栈内存
    freeList(&top);

    // 确认栈已为空
    printf("Is stack empty after free? %s\n", isEmpty(top) ? "Yes" : "No");

    return 0;
}
