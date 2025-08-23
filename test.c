#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;

} Node;

// ...existing code...
void Insert(Node **head, int data)
{
    Node *temp = malloc(sizeof *temp);
    if (temp == NULL)
    {
        fprintf(stderr, "malloc failed\n");
        // 若需要，可在此释放已有节点再退出
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;
    if (*head == NULL)
    {
        *head = temp;
        return;
    }
    // 需要遍历到最后一个节点
    Node *temp2 = *head;
    while (temp2->next != NULL)
    {
        temp2 = temp2->next;
    }
    temp2->next = temp;
    temp->prev = temp2;
}

void freeList(Node **head)
{
    Node *cur = *head;
    while (cur != NULL)
    {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}
// ...existing code...
int main()
{
    Node *head = NULL;
    Insert(&head, 3);
    Insert(&head, 4);
    Insert(&head, 5);
    Insert(&head, 6);
    Insert(&head, 7);
    Print(head);

    freeList(&head); // 释放内存

    return 0;
}