#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *link;
};
void insert(int data, struct Node *head);

int main()
{
    struct Node *head = NULL; // 定义一个头结点
    // 动态分配一个结构体
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    // 分配数据
    temp->data = 2;
    temp->link = NULL;
    head = temp; // 将头结点指向新建的节点

    // 插入数据 3
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = 3;
    temp->link = NULL;
    // 需要先遍历到最后一个节点
    struct Node *temp1 = head;
    while (temp1->link != NULL)
    {
        temp1 = temp1->link; // 只要下一个节点不为空，就会一直移动指针
    }
    // 修改最后一个节点的指向
    temp1->link = temp;
    // 插入数据 6
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = 6;
    temp->link = NULL;
    // 遍历链表
    temp1 = head;
    while (temp1->link != NULL)
    {
        temp1 = temp1->link;
    }
    // 修改最后一个节点的指向
    temp1->link = temp;
    // 使用insert函数插入数据
    insert(7, head);
    insert(8, head);
    insert(9, head);
    insert(10, head);

    // 打印链表
    temp1 = head;
    /* 1. 先将temp1指向头结点head; head -> n1--> n2-->n3->NULL
       2. temp1不为空，执行temp1 = temp1->link也就是temp1指向下一个节点N1，N1不为空，继续执行temp1 = temp1->link
         temp1指向下一个节点N2，N2不为空，继续执行temp1 = temp1->link
         temp1指向下一个节点N3，N3不为空，继续执行temp1 = temp1->link
         temp1指向NULL，结束循环
        3. temp1最终指向N3，也就是最后一个节点。
    */
    // temp1->link != NULL,这样打印直接跳过了最后一个节点，应修改为：temp1 != NULL
    while (temp1 != NULL)
    {
        printf("Node: %d, link: %p, next_link:%p--->\n", temp1->data, temp1, temp1->link);
        temp1 = temp1->link;
    }
    printf("head: %p, temp1=%p\n", head, temp1); // 应为NULL，0
                                                 // free(head);
    return 0;
}

void insert(int data, struct Node *head)
{ // 创建一个新节点，并赋值
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = NULL;
    // 如果头结点为空，则将新节点作为头结点
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        struct Node *temp = head;
        while (temp->link != NULL)
        {
            temp = temp->link; // 遍历到最后一个节点
        }
        temp->link = newNode; // 将链表的最后一个节点链接到新节点
    }
}
/*  优化代码
#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *link;
};
// 使用双指针修改头节点
void insert(int data, struct Node **head, struct Node **tail)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = NULL;

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->link = newNode;
        *tail = newNode;
    }
}
void freeList(struct Node *head)
{
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->link;
        free(temp);
    }
}
int main()
{
    struct Node *head = NULL;
    struct Node *tail = NULL; // 维护尾指针

    // 使用insert函数统一插入节点
    insert(2, &head, &tail);
    insert(3, &head, &tail);
    insert(6, &head, &tail);
    insert(7, &head, &tail);
    insert(8, &head, &tail);
    insert(9, &head, &tail);
    insert(10, &head, &tail);
    // 打印链表
    struct Node *temp = head;
    while (temp != NULL) {
        printf("Node: %d, link: %p, next_link: %p--->\n",
               temp->data, (void*)temp, (void*)temp->link);
        temp = temp->link;
    }
    printf("head: %p, tail: %p\n", (void*)head, (void*)tail);
    // 释放内存
    freeList(head);
    return 0;
}
*/