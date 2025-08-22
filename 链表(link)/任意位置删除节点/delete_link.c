#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void Insert(Node **head, int data, int n)
{
    Node *temp1 = (Node *)malloc(sizeof(Node));
    temp1->data = data;
    temp1->next = NULL;
    if (n == 1)
    {
        temp1->next = *head;
        *head = temp1;
        // 记得结束函数
        return;
    }
    // 其他位置
    Node *temp2 = *head;
    // 遍历到n-1的节点，需要循环N-2次；
    for (int i = 0; i < n - 2; i++)
    {
        temp2 = temp2->next;
    }
    // 重新链接节点
    temp1->next = temp2->next;
    temp2->next = temp1;
}
void Print(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
void freeList(Node *head)
{
    Node *temp = head; // 定义一个临时指针
    while (head != NULL)
    {
        temp = head;       // // 每次都指向head指针的位置
        head = head->next; // 指向下一个节点 head = temp->next也可以;
        free(temp);        // 释放当前节点
    }
    printf("The memory has been released!");
}

void Delete(Node **head, int n)
{
    Node *temp = *head;
    if (n == 1)
    {
        *head = temp->next;
        // 这里也要释放内存；
        free(temp);
        return;
    }
    // 将指针指向N-1节点位置，需要N-2的循环
    for (int i = 0; i < n - 2; i++)
    {
        temp = temp->next;
    }
    // 修复链表
    Node *temp2 = temp->next; // temp2指向要删掉的节点，以便可以释放内存
    temp->next = temp->next->next;
    free(temp2);
}
int main()
{
    Node *head = NULL;
    Insert(&head, 2, 1); // list: 2
    Insert(&head, 3, 2); // list: 2,3
    Insert(&head, 4, 1); // list: 4,2,3
    Insert(&head, 5, 2); // list: 4,5,2,3
    Insert(&head, 8, 5); // list: 4,5,2,3，8
    Insert(&head, 9, 5); //  4 -> 5 -> 2 -> 3 -> 9 -> 8 -> NULL
    Print(head);
    Delete(&head, 6);
    Print(head);
    Delete(&head, 3);
    Print(head);
    freeList(head);

    return 0;
}