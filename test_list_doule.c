#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

void Insert(Node **head, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void Print(Node *head)
{
    printf("Forward: ");
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d", temp->data);
        if (temp->next != NULL)
            printf(" <-> ");
        temp = temp->next;
    }
    printf(" -> NULL\n");

    printf("Backward: ");
    temp = head;
    // temp->next != NULL单链表
    while (temp != NULL && temp->next != NULL)
    {
        temp = temp->next;
    }
    while (temp != NULL)
    {
        printf("%d", temp->data);
        if (temp->prev != NULL)
            printf(" <-> ");
        temp = temp->prev;
    }
    printf(" -> NULL\n");
}

void FreeList(Node **head)
{
    if (head == NULL || *head == NULL)
    {
        printf("List is already empty\n");
        return;
    }

    Node *current = *head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL; // 重要：将头指针设置为NULL
    printf("The memory has been released\n");
}

int Delete(Node **head, int position)
{
    if (head == NULL || *head == NULL)
    {
        printf("List is empty, nothing to delete\n");
        return 1;
    }

    if (position < 1)
    {
        printf("Invalid position: %d. Position must be >= 1\n", position);
        return 2;
    }

    Node *temp = *head;

    // 删除第一个节点
    if (position == 1)
    {
        *head = temp->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
        free(temp);
        return 3;
    }

    // 找到要删除的节点
    // 防止删除节点的位置，超出链表自身的长度；
    for (int i = 1; temp != NULL && i < position; i++)
    {
        temp = temp->next;
    }
    // 超出之后，temp 指向 NULL；
    if (temp == NULL)
    {
        printf("Position %d exceeds list length\n", position);
        return 4;
    }

    // 调整前后节点的指针
    //
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }

    free(temp);
    return 0;
}

int main()
{
    Node *head = NULL;

    Insert(&head, 3);
    Insert(&head, 4);
    Insert(&head, 5);
    Insert(&head, 6);
    Insert(&head, 7);

    printf("Original list:\n");
    Print(head);

    printf("\nDeleting position 3:\n");
    Delete(&head, 3);
    Print(head);
    printf("head = %p, *head = %p", &head, head);

    printf("\nDeleting position 1:\n");
    Delete(&head, 1);
    Print(head);
    printf("head = %p, *head = %p", &head, head);

    printf("\nDeleting position 3 (invalid):\n");
    int ok = Delete(&head, 3);
    printf("%d\n", ok);
    Print(head);

    printf("\nFreeing list:\n");
    FreeList(&head);

    printf("\nTrying to delete from empty list:\n");
    Delete(&head, 1);

    return 0;
}