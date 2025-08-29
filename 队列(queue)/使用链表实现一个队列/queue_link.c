#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 定义单个节点
typedef struct Node
{
    int data;
    struct Node *next;
} Node;
typedef struct
{
    Node *head;
    Node *tail;
} Queue; // 定义指向节点的头尾指针

// 头尾指针初始化
void initQueue(Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}
// 创建一个节点
Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) // 判断内存是否分配成功
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // 赋值
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// 判断队列链表是否为空
bool isempty(Queue *q)
{
    return (q->head == NULL && q->tail == NULL);
}
// 入队
void enQueue(Queue *q, int data)
{
    Node *newNode = createNode(data);
    // 链表为空
    if (q->head == NULL && q->tail == NULL)
    { // 头尾指针指向同一个节点
        q->head = newNode;
        q->tail = newNode;
        return;
    }
    // 队尾节点指向新创建的节点
    q->tail->next = newNode;
    // 更新尾节点到新创建的节点
    q->tail = newNode;
}
// 出队
void dequeue(Queue *q)
{ // 队列链表是否为空
    if (isempty(q))
    {
        printf("Error: No element to dequeue!\n");
        return;
    }
    Node *temp = q->head;
    // front与rear指向同一个节点 在执行出队操作，就是一个空队列，也就是NULL
    if (q->head == q->tail)
    {
        q->head = q->tail = NULL;
        free(temp);
        return;
    }
    // head指针指向下一个节点
    q->head = temp->next;
    free(temp); // 释放该删除节点的内存
}
// 头结点的数据
int frontValue(Queue *q)
{
    if (q->head == NULL)
    {
        printf("Queue is empty\n");
        return -1;
    }
    return q->head->data;
}
// 尾结点的数据
int rearValue(Queue *q)
{
    if (q->head == NULL)
    {
        printf("Queue is empty\n");
        return -1;
    }
    return q->tail->data;
}
// 打印链表
void Print(Queue *q)
{
    if (isempty(q))
    {
        printf("NULL\n");
        return;
    }
    Node *temp = q->head;
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
// 释放链表
void freeQueue(Queue *q)
{
    Node *temp = q->head;
    while (q->head != NULL)
    {
        temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    initQueue(q); // 将head与tail指针指向NULL
    printf("The memory has been released\n");
}
int main()
{
    Queue q;
    initQueue(&q);
    dequeue(&q);
    Print(&q);
    printf("-----------------\n");
    enQueue(&q, 2);
    Print(&q);
    enQueue(&q, 3);
    Print(&q);
    enQueue(&q, 4);
    Print(&q);
    enQueue(&q, 5);
    Print(&q);
    enQueue(&q, 8);
    Print(&q);
    printf("---------------------\n");
    dequeue(&q);
    Print(&q);
    printf("front = %d, rear = %d\n", frontValue(&q), rearValue(&q));
    dequeue(&q);
    Print(&q);
    printf("front = %d, rear = %d\n", frontValue(&q), rearValue(&q));
    freeQueue(&q);
    return 0;
}