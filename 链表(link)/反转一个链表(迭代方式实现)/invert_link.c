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
        return;
    }
    Node *temp2 = *head;
    // 移动到N-1节点，循环N-2次；
    for (int i = 0; i < n - 2; i++)
    {
        temp2 = temp2->next;
    }
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
    Node *temp;
    while (head != NULL)
    {
        temp = head;       // // 每次都指向head指针的位置
        head = head->next; // 指向下一个节点 head = temp->next也可以;
        free(temp);        // 释放当前节点
    }
    printf("The memory has been released!\n");
}
void Delete(Node **head, int n)
{
    Node *temp1 = *head;
    if (n == 1)
    {
        *head = temp1->next;
        free(temp1);
        return;
    }
    // 移动到N-1节点，循环N-2次；
    for (int i = 0; i < n - 2; i++)
    {
        temp1 = temp1->next;
    }
    Node *temp2 = temp1->next; // temp2指向要删掉的节点，以便可以释放内存
    temp1->next = temp2->next; // temp1->next = temp1->next->next;
    free(temp2);
}
/*
1.当链表为空，current 就为 NULL，跳过循环，head 指向 NULL；（无问题）
2.当链表只有一个元素，current 就为 N1， current->next 为 NULL；也就是 Next 为 NULL；N1 指向 prev(NULL); prev 指向 N1， Current 为 NULL；跳出循环，head 指向 N1，（无问题）
*/
void Invert(Node **head)
{
    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;
    // 最后一次循环，next与current指向NULL，prev指向链表的最后一个节点
    while (current != NULL)
    {
        next = current->next; // 保存当前节点的下一个节点
        current->next = prev; // 将当前节点指向前一个节点
        // 更新节点
        prev = current;
        current = next;
    }
    // fix 头结点
    *head = prev;
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
    Invert(&head);
    Print(head);
    freeList(head);

    return 0;
}