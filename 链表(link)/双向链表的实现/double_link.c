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
    Node *temp = (Node *)malloc(sizeof(Node));
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
void Print(Node *head)
{
    printf("-------------------\n");
    Node *temp = head;
    // 打印，将其当做一个单链表；
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}
void freeList(Node *head)
{
    if (head == NULL)
    {
        printf("List is already empty\n");
        return;
    }
    Node *temp = head;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("The memory has been released");
}
void Delete(Node **head, int n)
{
    // 链表为空，不需要删除
    if (head == NULL || *head == NULL)
    {
        printf("List is empty, nothing to delete!\n");
        return;
    }
    /*
    这个条件是什么意思if (head == NULL || head == NULL)，不是只要判断head == NULL吗，为什么还要判断head == NULL
    因为两者检查的对象不同，缺一不可来保证安全和正确：
head 是函数参数（Node **）。如果调用者传了 NULL（例如写错或传参时出了问题），直接解引用 *head 会导致段错误。
*head 是链表的头指针本身，判断它为 NULL 表示链表为空，无需删除节点。
所以写成 if (head == NULL || *head == NULL) 是防御性编程：先确认参数合法，再确认链表非空。
建议写法（更清晰的错误说明）：
// ...existing code...
int Delete(Node **head, int position)
{
    if (head == NULL)
    {
        fprintf(stderr, "Delete: invalid argument head == NULL\n");
        return 1;
    }
    if (*head == NULL)
    {
        printf("List is empty, nothing to delete\n");
        return 1;
    }
}
    为什么head == NULL表示非法参数，没有理解，请举例说明
    因为函数参数 head 的类型是 Node **（指向指针的指针）。把它拆开看：

head 是一个指针变量，指向调用者的头指针（即它保存了调用者头指针变量的地址）。
*head 是调用者的头指针本身（指向第一个节点），当链表为空时 *head == NULL。
所以两种 NULL 含义不同：

head == NULL：调用者没有传入“指针的地址”，参数本身无效（非法参数）。若不先检测就做 *head，会导致解引用 NULL（段错误）。
*head == NULL：参数合法，但链表为空，没东西可删，这是正常情况。
举例说明：

正确用法（安全）——把头指针变量的地址传入
Node *head = NULL;
Delete(&head, 1); // head != NULL（参数合法），但 *head == NULL（链表为空）
错误用法（非法参数，head==NULL）——传入 NULL 作参数：
Delete(NULL, 1); // 直接把 NULL 传给函数，函数内若执行 *head 会崩溃
另一种错误场景：指针变量本身是 NULL，然后把它传入：
Node **hp = NULL;
Delete(hp, 1); // hp == NULL，同样是非法参数。
因此写成
if (head == NULL || *head == NULL) { /* 先检查参数，再检查链表是否为空
是防御性编程：先确认参数合法（避免解引用 NULL 导致崩溃），再处理链表为空的情况。 */

    // 位置为负数
    if (n < 1)
    {
        printf("Invalid position: %d, Position must be >= 1\n", n);
        return;
    }
    Node *temp = *head;
    if (n == 1)
    {
        *head = temp->next;

        // temp->next->prev = NULL;没有考虑链表为1的情况
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
        free(temp);
        return;
    }
    // 跟单链表一样；需要达到N节点；
    // 防止删除节点的位置，超出链表自身的长度；
    // temp != NULL && i < n - 1,确保正确位置会移动到n节点，非法位置temp会移动到NULL
    for (int i = 0; temp != NULL && i < n - 1; i++)
    {
        temp = temp->next;
    }
    // 在增加非法位置执行逻辑
    // 超出之后，temp 指向 NULL；
    if (temp == NULL)
    {
        printf("Position %d exceeds list length\n", n);
        return;
    }
    // 修复链表；
    // if (temp->next == NULL)
    // {
    //     temp->prev->next = NULL;
    // }
    // else
    // {
    //     temp->prev->next = temp->next;
    //     temp->next->prev = temp->prev;
    // }
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    if (temp->prev != NULL)
    { // 当temp->next == NULL时，等价于temp->prev->next = NULL
        temp->prev->next = temp->next;
    }
    free(temp);
}
int main()
{
    Node *head = NULL;
    Insert(&head, 3);
    Insert(&head, 4);
    Insert(&head, 5);
    Insert(&head, 6);
    Insert(&head, 7);
    Insert(&head, 8);
    Print(head);
    Delete(&head, 1);
    Print(head);
    Delete(&head, 3);
    Print(head);
    Insert(&head, 10);
    Print(head);
    Delete(&head, 5);
    Print(head);
    freeList(head);
    printf("head = %p, *head = %p", &head, head);
    printf("\n----------------------\n");
    head = NULL;

    Insert(&head, 3);
    Insert(&head, 4);
    Insert(&head, 5);
    Insert(&head, 6);
    Insert(&head, 7);

    printf("Original list:\n");
    Print(head); // 34567

    printf("\nDeleting position 3:\n");
    Delete(&head, 3); // 3467
    Print(head);
    printf("head = %p, *head = %p", &head, head);

    printf("\nDeleting position 1:\n");
    Delete(&head, 1); // 467
    Print(head);
    printf("head = %p, *head = %p", &head, head);

    printf("\nDeleting position 4 (invalid):\n");
    Delete(&head, 4);
    Print(head);

    printf("\nFreeing list:\n");
    freeList(head);
    printf("\nhead = %p, *head = %p", &head, head);
    head = NULL;
    printf("\nhead = %p, *head = %p", &head, head);
    printf("\nTrying to delete from empty list:\n");
    Delete(&head, 1);

    return 0;
}

/*
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
*/