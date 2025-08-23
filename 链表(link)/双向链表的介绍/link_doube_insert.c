#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 双链表节点结构
typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// 双链表结构
typedef struct
{
    Node *head;
    Node *tail;
    int size;
} DoublyLinkedList;

// 初始化双链表
void initList(DoublyLinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// 创建新节点
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        printf("内存分配失败!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 插入函数：按位置插入，若不提供位置则默认从尾部插入
bool insert(DoublyLinkedList *list, int data, int position)
{
    // 如果位置为-1，表示未提供位置参数，默认插入到尾部
    if (position == -1)
    {
        position = list->size; // 设置为最后一个位置之后
    }

    // 检查位置是否有效
    if (position < 0 || position > list->size)
    {
        printf("无效的位置: %d。有效范围: 0 到 %d\n", position, list->size);
        return false;
    }

    Node *newNode = createNode(data);

    // 如果链表为空
    if (list->size == 0)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    // 插入到头部
    else if (position == 0)
    {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    // 插入到尾部
    else if (position == list->size)
    {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    // 插入到中间位置
    else
    {
        // 找到要插入位置的前一个节点
        Node *current;
        // 根据位置决定从头部还是尾部开始遍历以提高效率
        if (position < list->size / 2)
        {
            current = list->head;
            for (int i = 0; i < position - 1; i++)
            {
                current = current->next;
            }
        }
        else
        {
            current = list->tail;
            // 等价于 (int i = 0; i < size - positioon; i++)
            for (int i = list->size - 1; i > position - 1; i--)
            {
                current = current->prev;
            }
        }

        // 插入新节点
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }

    list->size++;
    return true;
}

// 打印链表
void printList(DoublyLinkedList *list)
{
    Node *current = list->head;
    printf("链表内容: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 反向打印链表
void printListReverse(DoublyLinkedList *list)
{
    Node *current = list->tail;
    printf("反向链表内容: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

// 释放链表内存
void freeList(DoublyLinkedList *list)
{
    Node *current = list->head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int main()
{
    DoublyLinkedList list;
    initList(&list);

    // 测试默认插入（尾部插入）
    printf("默认插入（尾部插入）:\n");
    insert(&list, 10, -1); // 不提供位置参数，默认尾部插入
    insert(&list, 20, -1);
    insert(&list, 30, -1);
    printList(&list);
    printListReverse(&list);

    // 测试按位置插入
    printf("\n按位置插入:\n");
    insert(&list, 5, 0);  // 插入到头部
    insert(&list, 25, 3); // 插入到中间位置
    insert(&list, 35, 5); // 插入到尾部
    printList(&list);
    printListReverse(&list);

    // 测试无效位置
    printf("\n测试无效位置:\n");
    insert(&list, 100, 10); // 无效位置

    // 释放内存
    freeList(&list);

    return 0;
}