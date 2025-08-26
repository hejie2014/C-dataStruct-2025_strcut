#include <stdio.h>
#include <stdlib.h>

/*==================== 1) 单链表节点定义 ====================*/
typedef struct Node
{
    int data;          // 节点中存放的数据
    struct Node *next; // 指向下一个节点的指针
} Node;

// 创建一个新的链表节点，返回其指针
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // 为新节点申请内存
    if (newNode == NULL)
    {
        fprintf(stderr, "malloc failed\n"); // 打印错误信息到标准错误
        exit(EXIT_FAILURE);                 // 异常退出
    }
    // 赋值
    newNode->data = data;
    newNode->next = NULL;
    return newNode; // 返回创建的节点指针
}
// 链表尾插法
void append(Node **head, int data)
{
    Node *newNode = createNode(data); // 调用createNode，创建新节点
    if (*head == NULL)                // 如果链表为空，新节点就是头节点
    {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    // 遍历到链表尾部
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode; // 新节点加到尾部
}
/* 打印链表：从 head 开始依次输出每个节点值 */
void printList(Node *head)
{
    Node *temp = head;
    if (temp == NULL)
    {
        printf("NULL\n");
        return;
    }
    while (temp != NULL) // 遍历直到遇到 NULL
    {
        printf("%d", temp->data); // 打印当前节点的数据
        if (temp->next != NULL)
        {
            printf(" -> "); // 打印箭头，最后一个节点只会打印数据
        }
        temp = temp->next; // 指针后移到下一个节点
    }
    printf(" -> NULL\n");
}
/* 释放整条链表占用的堆内存，防止内存泄漏 */
void freeList(Node **head)
{
    Node *temp = *head;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL; // 将指针设置为NULL
    printf("The memory has been released\n");
}
/*==================== 2) 链式栈定义与操作 ====================*/
// 栈节点：用来把“链表节点的指针”压栈
// 创建一个新链表，是该链表不存储int数据,而是Node结构体指针
typedef struct stackNode
{
    Node *listNode;         // 保存一个“链表节点”的指针
    struct stackNode *next; // 指向下一个“栈节点”
} stackNode;

/* 初始化栈：把 top 置为 NULL，表示空栈 */
void initStack(stackNode **top)
{
    *top = NULL; // 空栈
}
/* 判断栈是否为空：top 为 NULL 即空 */
int isEmpty(stackNode *top)
{
    return top == NULL; // 非 0 为真，0 为假
}
/* 压栈：把一个“链表节点指针”入栈 */
// 因为要修改top指针的指向，需要传入指针的指针，也就是二级指针，stackNode **top
void push(stackNode **top, Node *node)
{
    stackNode *newStackNode = (stackNode *)malloc(sizeof(stackNode)); // 申请栈节点,与之前的Node节点有区别
    if (newStackNode == NULL)
    {
        // 判空
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    newStackNode->listNode = node; // 把链表节点指针存进去
    newStackNode->next = *top;     // 新栈节点的 next 指向原栈顶
    *top = newStackNode;           // 更新栈顶为新栈节点
}
/* 出栈：弹出数据 */
void pop(stackNode **top)
{ // 判断栈是否为空
    if (*top == NULL)
    {
        printf("The stack is empty! Cannot pop.\n");
        return;
    }
    stackNode *temp = *top;
    *top = (*top)->next; // 栈顶下移
    free(temp);          // 释放被弹出的“栈节点”内存
}
// 获取栈顶节点
Node *topNodePtr(stackNode *top)
{
    return top->listNode;
}
/*==================== 3) 核心：用栈反转链表 ====================*/
/*
 * 思路：
 * 1) 遍历原链表，把每个“链表节点指针”依次 push 到栈里；
 * 2) 由于栈是后进先出（LIFO），先获取栈顶元素，在将之前的栈顶元素进行相连，在pop；
 * 3) 重复步骤2，最后把尾节点 next 置为 NULL。
 */
// reverse函数传入原链表的头指针，返回反转链表的头指针
Node *reverses(Node *head)
{
    if (head == NULL)
    {
        return NULL; // 空链表直接返回
    }
    stackNode *top = NULL; // 定义一个栈顶指针

    // 把链表的每个节点压入栈
    Node *temp = head;
    while (temp != NULL)
    {
        push(&top, temp);
        temp = temp->next;
    }
    // 开始出栈并修改链表指向
    temp = topNodePtr(top); // 指向链表最后一个节点
    head = temp;            // 修改头指针
    pop(&top);              // 出栈，为下一步做准备
    while (!isEmpty(top))
    {
        temp->next = topNodePtr(top);
        pop(&top);
        temp = temp->next; // 移动到下一个节点，也就是上一个节点。
    }
    temp->next = NULL; // 最后一个节点的 next 必须置 NULL（成为新尾）
    return head;       // 返回新的链表头
}

int main()
{
    Node *head = NULL;
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    append(&head, 6);
    printList(head);
    printf("------------------\n");

    printf("原链表: ");
    printList(head); // 打印原链表

    head = reverses(head);
    printf("反转后: ");
    printList(head); // 打印反转后的链表

    freeList(&head);
    printList(head);

    return 0;
}