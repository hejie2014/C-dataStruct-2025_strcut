#include <stdio.h>
#include <stdlib.h>
/*
你的代码报错的原因是 Node 结构体定义时没有使用 struct 关键字，导致编译器无法识别 Node *next;。
在 C 语言中，结构体类型需要用 struct Node，或者用 typedef struct Node Node;。
你已经用了 typedef struct Node { ... } Node;，但在结构体内部声明 Node *next; 时，编译器还没完成 Node 的定义，所以应该写成 struct Node *next;。
*/
typedef struct Node
{
    int data;
    struct Node *next;
} Node;
void Insert(Node **head, int x);
void Print(Node *head);
void freeList(Node *head);
int main()
{
    // 创建一个头指针
    Node *head = NULL;
    int n = 0, x = 0;
    printf("How many number?\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the number \n");
        scanf("%d", &x);
        Insert(&head, x);
        Print(head);
    }
    freeList(head);
    return 0;
}
// 传的是head的内容，不是head的地址，只不过head本身是个指针变量，存的是地址。想要改变head，需要传&head
void Insert(Node **head, int x)
{
    // 动态分配一个节点
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = x;
    temp->next = NULL;
    // 表示在链表的头部进行插入，每次都会更新头结点，指向新建的节点。
    if (*head != NULL)
        temp->next = *head;
    *head = temp;
}
/* 还是尽量使用一个临时变量，为它保留了传入的head副本不变（尽管在函数返回后head副本也会销毁，但循环过程中如果后面还想用head的值，比如再次遍历。保留原始头指针，便于调试或多次遍历
但是，为了代码的可读性和避免潜在的错误（例如，在循环后面误用了head），通常使用临时变量。5

*/
void Print(Node *head)
{
    Node *temp = head;
    printf("List: ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
/*
void Print(Node *head)
{
    printf("List: ");
    while (head != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
*/
// 释放内存
void freeList(Node *head)
{
    struct Node *temp; // 定义一个临时指针
    while (head != NULL)
    {
        temp = head;       // 每次都指向head指针的位置
        head = head->next; // 指向下一个节点
        free(temp);        // 释放当前节点
    }
    printf("memory clear!");
}