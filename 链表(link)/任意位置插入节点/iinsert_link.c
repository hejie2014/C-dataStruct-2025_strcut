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
    // 如果插入第一个位置
    if (n == 1)
    {
        temp1->next = *head;
        *head = temp1;
        return;
    }
    // 其他位置
    Node *temp2 = *head;
    // 需要遍历链表到N-1的节点位置(需要经历n-2次循环)，将新建的节点的next指向当前N,在将N-1的next指向temp1；
    for (int i = 0; i < n - 2; i++)
    {
        temp2 = temp2->next;
    }
    // 到达N-1的节点位置
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
    Node *temp; // 定义一个临时指针
    while (head != NULL)
    {
        temp = head;       // 每次都指向head指针的位置
        head = head->next; // 指向下一个节点
        free(temp);        // 释放当前节点
    }
    printf("memory clear!");
}
int main()
{
    Node *head = NULL;   // 空链表
    Insert(&head, 2, 1); // list: 2
    Insert(&head, 3, 2); // list: 2,3
    Insert(&head, 4, 1); // list: 4,2,3
    Insert(&head, 5, 2); // list: 4,5,2,3
    Print(head);
    freeList(head);
    return 0;
}