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
    if (q->front == -1 && q->rear == -1)
        return true;
    return false;
}
// 入队
void enqueue(Queue *q, int data)
{
    if ((q->rear + 1) % q->capacity == q->front) // rear的下一个位置与front重合，不能在进行赋值了，数组已满
    {
        printf("the queue is full!\n");
        return;
    }
    else if (isEmpty(q))
    {
        q->front = 0;
        q->rear = 0;
    }
    else
    {
        q->rear = (q->rear + 1) % q->capacity; // rear下标后移,一直循环
    }
    q->array[q->rear] = data; // 添加数据，rear下标后移
}
// 出队
void dequeue(Queue *q)
{
    if (isEmpty(q)) // 检查队列是否为空
    {
        printf("Error: No element to dequeue!\n");
        return;
    }
    else if (q->front == q->rear) // 存在一个元素，出队之后,就为空就让下标重置.数组就可以得到再次利用
    {                             // 设置为空状态
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % q->capacity;
    } // front下标后移
}
int front(Queue *q)
{
    return q->array[q->front];
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
    int number = q->front;
    // 两种情况，1.front在 rear前面，正常打印
    // 2. 1.front在 rear后面，先打印front到结尾部分，在打印0到rear部分数据
    if (q->front <= q->rear)
    {
        for (int i = number; i <= q->rear; i++) // 从front的下一个位置开始打印，到rear结束
        {
            printf("%d ", q->array[i]);
        }
    }
    else
    {
        // front到结尾部分
        for (int i = number; i < q->capacity; i++) // 从front的下一个位置开始打印，到rear结束
        {
            printf("%d ", q->array[i]);
        }
        // 0到rear部分数据
        for (int i = 0; i <= q->rear; i++)
        {
            printf("%d ", q->array[i]);
        }
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
    printf("\n----多出一个位置再次插入数据-----\n");
    enqueue(&q, 8);
    print(&q);
    printf("front = %d, rear = %d\n", front(&q), rear(&q));
    printf("--------------\n");
    dequeue(&q);
    print(&q);
    enqueue(&q, 10);
    print(&q);
    printf("front = %d, rear = %d\n", front(&q), rear(&q));
    freeQueue(&q);
    return 0;
}