#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void push(Node **top, int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    if (*top == NULL)
    {
        *top = temp;
        return;
    }
    temp->next = *top;
    *top = temp;
}
void pop(Node **top)
{
    Node *temp = *top;
    if (*top == NULL)
    {
        printf("the linkListed no element!\n");
        return;
    }
    *top = (*top)->next;
    free(temp);
}
int topValue(Node *top)
{
    if (top == NULL)
    {
        printf("the linkListed no element!\n");
        return;
    }
    return top->data;
}
bool isEmpty(Node *top)
{
    return (top == NULL);
}
void print(Node *top)
{
    Node *temp = top;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
void freeList(Node *top)
{
    Node *temp = top;
    while (top != NULL)
    {
        temp = top;
        top = top->next;
        free(temp);
    }
    printf("The memory has been released\n");
}
int main()
{
    Node *top = NULL; // 创建一个指向链表的节点
    pop(&top);
    push(&top, 1);
    print(top);
    push(&top, 2);
    print(top);
    push(&top, 4);
    print(top);
    push(&top, 3);
    print(top);
    push(&top, 8);
    print(top);
    printf("-----------------\n");
    pop(&top);
    print(top);
    printf("topValue = %d\n", topValue(top));
    pop(&top);
    print(top);
    freeList(top);
    top = NULL; // 指针指向空；
    return 0;
}