#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treeNode
{
    int data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;
// 队列节点
typedef struct queueNode
{
    treeNode *treeNodePtr;
    struct queueNode *next;
} queueNode;
// 队列的头尾指针
typedef struct
{
    queueNode *head;
    queueNode *tail;
} Queue;
// 初始化头尾指针
void initQueue(Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}
// 创建队列节点
queueNode *creatQueueNode(treeNode *node)
{
    queueNode *newNode = malloc(sizeof(queueNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // 赋值
    newNode->treeNodePtr = node;
    newNode->next = NULL;
    return newNode;
}
// 判断队列链表是否为空
bool isempty(Queue *q)
{
    return (q->head == NULL && q->tail == NULL);
}
// 入队
void enqueue(Queue *q, treeNode *Node)
{
    queueNode *newNode = creatQueueNode(Node);
    if (q->head == NULL && q->tail == NULL)
    {
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
{
    // 队列链表是否为空
    if (isempty(q))
    {
        printf("the queue is empty!\n");
        return;
    }
    queueNode *temp = q->head;
    // front与rear指向同一个节点 在执行出队操作，就是一个空队列，也就是NULL
    if (q->head == q->tail)
    {
        free(temp);
        initQueue(q); // 头尾指针置空；
        return;
    }
    // head指针指向下一个节点
    q->head = temp->next;
    free(temp); // 释放该删除节点的内存
}
// 返回队列的头节点地址
treeNode *frontValue(Queue *q)
{
    if (isempty(q))
        return NULL;
    return q->head->treeNodePtr;
}
// 返回队列的尾节点地址
treeNode *rearValue(Queue *q)
{
    if (isempty(q))
        return NULL;
    return q->tail->treeNodePtr;
}
// 打印队列
void Print(Queue *q)
{
    if (isempty(q))
    {
        printf("NULL\n");
        return;
    }
    queueNode *temp = q->head;
    while (temp != NULL)
    {
        printf("%d ", temp->treeNodePtr);
        if (temp->next != NULL)
        {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}
// 释放队列内存
void freeQueue(Queue *q)
{
    if (isempty(q))
        return;
    queueNode *temp = q->head;
    while (q->head != NULL)
    {
        temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    initQueue(q); // 将head与tail指针指向NULL
    printf("The memory has been released\n");
}

// 创建树节点
treeNode *createNode(int data)
{
    treeNode *newNode = malloc(sizeof(treeNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // 赋值
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// 插入树节点
treeNode *insert(treeNode *root, int data)
{
    if (root == NULL)
    {
        treeNode *newNode = createNode(data);
        root = newNode;
        return root;
    }
    // 找到正确的位置插入
    else if (data <= root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }
    return root;
}
// 查询数据
bool search(treeNode *root, int data)
{
    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    // 数据小于当前节点值，就去左边寻找
    else if (data < root->data)
    {
        return search(root->left, data);
    }
    else
    {
        return search(root->right, data);
    }
}

// 广度优先，层次遍历
void levelOrder(treeNode *root)
{
    /*
    在 C 中，= 是赋值运算符，== 是相等比较运算符
    检查指针是否为 NULL 时一定要用 ==
    养成用 if (NULL == ptr) 这样的写法可以避免意外用 = 的错误（因为 NULL = ptr 不能编译）
    */
    if (root == NULL)
        return;
    // 先声明一个队列的头尾指针
    Queue q;
    // 初始化头尾指针
    initQueue(&q);
    // 现将tree的root节点加入到队列中
    enqueue(&q, root);
    // printf("--------test------------\n");
    while (!isempty(&q))
    { // 取队列的最前面的节点地址
        treeNode *current = frontValue(&q);
        printf("%d ", current->data);
        // 当前节点有左孩子，加入队列
        if (current->left != NULL)
        {
            enqueue(&q, current->left);
        }
        // 当前节点有右孩子，加入队列
        if (current->right != NULL)
        {
            enqueue(&q, current->right);
        }
        dequeue(&q); // 将该节点出队；
    }
}

// 中序遍历
void inorderTraversal(treeNode *root)
{
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}
// 释放内存
void freeTree(treeNode *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main()
{
    treeNode *root = NULL;
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 8);
    root = insert(root, 12);
    root = insert(root, 18);
    root = insert(root, 21);
    root = insert(root, 23);
    root = insert(root, 28);
    root = insert(root, 27);
    inorderTraversal(root);                     // 8 10 12 15 18 20 21 23 25 27 28
    printf("\nresult = %d\n", search(root, 3)); // result = 0
    printf("result = %d\n", search(root, 8));   // result = 1
    printf("-----测试测序遍历函数------\n");
    Queue q;
    initQueue(&q);
    printf("rootaddress = %d\n", root);
    printf("queue is empty = %d\n", isempty(&q));
    enqueue(&q, root);
    enqueue(&q, root->left);
    enqueue(&q, root->right);
    printf("front = %d, rear = %d\n", frontValue(&q), rearValue(&q));
    Print(&q);
    printf("queue is empty = %d\n", isempty(&q));
    dequeue(&q);
    Print(&q);
    freeQueue(&q);
    /*  ----- 队列函数test结果-----
    -----测试测序遍历函数------
    rootaddress = 1848435104
    queue is empty = 1
    front = 1848435104, rear = 1848435296
    1848435104  -> 1848435616  -> 1848435296  -> NULL
    queue is empty = 0
    1848435616  -> 1848435296  -> NULL
    The memory has been released
    */
    printf("-----测试levelOrder函数------\n");
    levelOrder(root); // 结果应为 15 10 20 8 12 18 25 21 28 23 27

    freeTree(root);
    root = NULL;
    return 0;
}