#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 5

// 定义一个结构体，包括数组，队头，队尾和容量
typedef struct
{
    int *array;   // 数组
    int front;    // 队头
    int rear;     // 队尾
    int capacity; // 初始容量
} Queue;
// 队列的初始化
void initQueue(Queue *q, int capacity)
{ // 动态分配内存
    q->array = malloc(sizeof(int) * capacity);
    // 判断内存是否分配成功
    if (q->array == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    // 初始化
    q->front = -1;
    q->rear = -1;
    q->capacity = capacity;
}
bool isEmpty(Queue *q) // 传入一个结构体指针
{                      // 头与尾相等则队列为空
    if (q->front == q->rear)
        return true;
    return false;
}
// 入队
void enqueue(Queue *q, int data)
{
    if (q->rear == q->capacity - 1) // capacity - 1到达数组最后一个位置
    {
        int newCapacity = q->capacity * 2; // 扩大容量
        // 重新分配内存
        int *new_array = realloc(q->array, sizeof(int) * newCapacity);
        if (new_array == NULL) // 判断内存是否分配成功
        {
            printf("Memory allocation failed\n");
            return;
        }
        q->array = new_array;      // 指针指向新分配的内存地址
        q->capacity = newCapacity; // 更新容量大小
        printf("Array resized to %d\n", newCapacity);
    }
    q->array[++(q->rear)] = data; // 添加数据，rear下标后移
}
// 出队
void dequeue(Queue *q)
{
    if (isEmpty(q)) // 检查队列是否为空
    {
        printf("Error: No element to dequeue!\n");
        return;
    }
    q->front++; // front下标后移
}
int front(Queue *q)
{
    int i = q->front + 1; // 是当前位置的下一个数据，所以 +1
    return q->array[i];
}
int rear(Queue *q)
{
    return q->array[q->rear]; // 返回队尾数据
}
// 打印队列
void print(Queue *q)
{ // 队列是否为空
    if (isEmpty(q))
    {
        printf("the queue is empty!\n");
        return;
    }
    printf("Queue: ");
    int number = q->front + 1;
    for (int i = number; i <= q->rear; i++) // 从front的下一个位置开始打印，到rear结束
    {
        printf("%d ", q->array[i]);
    }
    printf("\n");
}
// 释放队列
void freeQueue(Queue *q)
{
    free(q->array);
    q->array = NULL;
    q->front = -1;
    q->rear = -1;
    q->capacity = 0;
}
int main()
{
    Queue q;
    initQueue(&q, INITIAL_CAPACITY);
    dequeue(&q);
    print(&q);
    //  printf("front = %d, rear = %d", front(&q), rear(&q)); 垃圾值
    enqueue(&q, 2);
    print(&q);
    enqueue(&q, 3);
    print(&q);
    enqueue(&q, 4);
    print(&q);
    enqueue(&q, 6);
    print(&q);
    enqueue(&q, 7);
    print(&q);
    enqueue(&q, 8);
    print(&q);
    printf("----------------\n");
    dequeue(&q);
    print(&q);
    printf("front = %d, rear = %d", front(&q), rear(&q));
    freeQueue(&q);
    return 0;
}