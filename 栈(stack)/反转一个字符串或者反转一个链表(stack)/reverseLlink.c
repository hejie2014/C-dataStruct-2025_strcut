#include <stdio.h>  // 引入标准输入输出库（printf 等）
#include <stdlib.h> // 引入标准库（malloc/free/exit 等）

/*==================== 1) 单链表节点定义 ====================*/
typedef struct Node
{
    int data;          // 节点中存放的数据
    struct Node *next; // 指向下一个节点的指针
} Node;

/* 创建一个新的链表节点，返回其指针 */
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // 为新节点申请内存
    if (!newNode)
    {                                       // 判空，防止申请失败
        fprintf(stderr, "malloc failed\n"); // 打印错误信息到标准错误
        exit(EXIT_FAILURE);                 // 异常退出
    }
    newNode->data = data; // 填入数据
    newNode->next = NULL; // 新节点默认不指向任何节点
    return newNode;       // 返回新节点指针
}
// 链表尾插法
void append(Node **head, int data)
{
    Node *newNode = createNode(data); // 创建新节点

    if (*head == NULL)
    { // 如果链表为空，新节点就是头节点
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL)
    { // 遍历到链表尾部
        temp = temp->next;
    }
    temp->next = newNode; // 新节点加到尾部
}

/* 打印链表：从 head 开始依次输出每个节点值 */
void printList(Node *head)
{
    Node *temp = head; // 临时指针从头开始
    while (temp != NULL)
    {                                 // 遍历直到遇到 NULL
        printf("%d -> ", temp->data); // 打印当前节点的数据
        temp = temp->next;            // 指针后移到下一个节点
    }
    printf("NULL\n"); // 末尾标识
}

/*（可选）释放整条链表占用的堆内存，防止内存泄漏 */
void freeList(Node *head)
{
    while (head)
    {                      // 只要还有节点
        Node *tmp = head;  // 暂存当前节点
        head = head->next; // 先移动 head
        free(tmp);         // 再释放当前节点
    }
}

/*==================== 2) 链式栈定义与操作 ====================*/
/* 栈节点：用来把“链表节点的指针”压栈 */
typedef struct StackNode
{
    Node *listNode;         // 保存一个“链表节点”的指针
    struct StackNode *next; // 指向下一个“栈节点”
} StackNode;

/* 栈结构：只需要一个指向栈顶的指针即可 */
typedef struct
{
    StackNode *top; // 指向当前栈顶的指针
} Stack;

/* 初始化栈：把 top 置为 NULL，表示空栈 */
void initStack(Stack *s)
{
    s->top = NULL; // 空栈
}

/* 判断栈是否为空：top 为 NULL 即空 */
int isEmpty(Stack *s)
{
    return s->top == NULL; // 非 0 为真，0 为假
}

/* 压栈：把一个“链表节点指针”入栈 */
void push(Stack *s, Node *node)
{
    StackNode *newStackNode = (StackNode *)malloc(sizeof(StackNode)); // 申请栈节点
    if (!newStackNode)
    { // 判空
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    newStackNode->listNode = node; // 把链表节点指针存进去
    newStackNode->next = s->top;   // 新栈节点的 next 指向原栈顶
    s->top = newStackNode;         // 更新栈顶为新栈节点
}

/* 出栈：弹出并返回一个“链表节点指针” */
Node *pop(Stack *s)
{
    if (isEmpty(s))
        return NULL;             // 空栈返回 NULL（调用方需注意判空）
    StackNode *temp = s->top;    // 暂存当前栈顶节点
    Node *node = temp->listNode; // 取出里面保存的“链表节点指针”
    s->top = temp->next;         // 栈顶下移
    free(temp);                  // 释放被弹出的“栈节点”内存
    return node;                 // 返回弹出的“链表节点指针”
}

/*==================== 3) 核心：用栈反转链表 ====================*/
/*
 * 思路：
 * 1) 遍历原链表，把每个“链表节点指针”依次 push 到栈里；
 * 2) 由于栈是后进先出（LIFO），pop 出来的顺序正好是反的；
 * 3) 依次把 pop 出来的节点重新 next 相连，最后把尾节点 next 置为 NULL。
 */
Node *reverseUsingStack(Node *head)
{
    if (head == NULL)
        return NULL; // 空链表直接返回

    Stack s;       // 定义一个栈
    initStack(&s); // 初始化栈为“空栈”

    /* Step 1：把整条链表的每个节点压入栈 */
    Node *current = head; // 从头开始遍历
    while (current != NULL)
    {                            // 遍历到 NULL 为止
        push(&s, current);       // 把当前节点指针压栈
        current = current->next; // 后移到下一个节点
    }

    /* Step 2：开始出栈并重连指针 */
    head = pop(&s); // 弹出第一个（原尾部）作为新的“头结点”
    current = head; // current 指向新链表的“当前尾部”
    while (!isEmpty(&s))
    {                            // 只要栈不空，就继续弹
        current->next = pop(&s); // 把弹出的节点接到 current 的后面
        current = current->next; // current 后移，指向新链表的最后一个节点
    }
    current->next = NULL; // 最后一个节点的 next 必须置 NULL（成为新尾）

    return head; // 返回新的链表头
}

/*==================== 4) 测试：构造、反转、打印、释放 ====================*/
int main()
{
    // 手动构造链表：1 -> 2 -> 3 -> 4 -> NULL
    Node *head = createNode(1);             // 头结点 1
    head->next = createNode(2);             // 1 -> 2
    head->next->next = createNode(3);       // 1 -> 2 -> 3
    head->next->next->next = createNode(4); // 1 -> 2 -> 3 -> 4

    printf("原链表: ");
    printList(head); // 打印原链表

    head = reverseUsingStack(head); // 调用“栈反转”函数

    printf("反转后: ");
    printList(head); // 打印反转后的链表

    freeList(head); // 释放链表内存（良好习惯）
    return 0;       // 正常结束
}
