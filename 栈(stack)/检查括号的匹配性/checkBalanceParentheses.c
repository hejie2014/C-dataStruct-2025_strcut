#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

Node *createNode(char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        fprintf(stderr, "malloc failed\n"); // 打印错误信息到标准错误
        exit(EXIT_FAILURE);                 // 异常退出
    }
    // 赋值
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Node **top, char data)
{
    Node *newNode = createNode(data);
    if (*top == NULL)
    {
        *top = newNode;
        return;
    }
    newNode->next = *top;
    *top = newNode;
}
void pop(Node **top)
{
    Node *temp = *top;
    if (*top == NULL)
    {
        printf("The stack is empty! Cannot pop.\n");
        return;
    }
    *top = (*top)->next;
    free(temp);
}
char topValue(Node *top)
{
    return top->data;
}
bool isEmpty(Node *top)
{
    return top == NULL;
}
// 打印链表
void Print(Node *top)
{
    if (isEmpty(top))
    {
        printf("NULL\n");
        return;
    }
    Node *temp = top;
    while (temp != NULL)
    {
        printf("%c", temp->data);
        if (temp->next != NULL)
        {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}
// 释放链表
void freeList(Node **top)
{
    Node *temp = *top;
    while (*top != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
    *top = NULL; // 将指针设置为NULL
    printf("the memory has been released!\n");
}
// 判断符号是否匹配
bool isPair(char opening, char closing)
{
    if (opening == '(' && closing == ')')
        return true;
    else if (opening == '[' && closing == ']')
        return true;
    else if (opening == '{' && closing == '}')
        return true;
    return false;
}
bool checkBalanceParentheses(char *exp)
{
    int number = strlen(exp); // 字符串的长度，来决定循环次数
    Node *top = NULL;         // 定义一个栈顶指针
    for (int i = 0; i < number; i++)
    { // 遇到符号就压栈
        if (exp[i] == '[' || exp[i] == '(' || exp[i] == '{')
        {
            push(&top, exp[i]); // 压栈
        }
        else if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') // 判断符号是否匹配
        {                                                         // 进行匹配时，栈为空，或者符号不匹配，就释放链表，并返回false
            if (isEmpty(top) || !isPair(topValue(top), exp[i]))
            {
                Print(top);
                freeList(&top);
                return false;
            }
            else // 不为空，匹配成功就pop
                pop(&top);
        }
    }
    bool result = isEmpty(top) ? true : false;
    Print(top);
    freeList(&top);
    return result;
}

int main()
{
    Node *top = NULL;
    // printf("Is stack empty after free? %s\n", isEmpty(top) ? "Yes" : "No");
    // pop(&top);
    push(&top, '(');
    push(&top, '2');
    push(&top, '+');
    push(&top, '3');
    push(&top, ')');
    Print(top);
    pop(&top);
    Print(top);
    freeList(&top);
    printf("------------------------\n");
    char exp[] = "{[(2 + 3) + (2 + 1]]}";
    printf("%d\n", strlen(exp));
    /*
    原因：这一行会导致编译错误，因为你把一个指针表达式（条件运算符返回的 const char *）用来初始化字符数组（char A[]）。条件表达式的结果类型是指针，不能用于数组初始化。
    简短说明：char A[] = "..." 只在编译期用常量字符串直接初始化时有效；条件表达式结果是运行时的指针，必须用 char * 或 const char * 来接收。
    */
    char *A = checkBalanceParentheses(exp) ? "yes" : "NO";
    printf("Whether the expression matches: %s", A);
    return 0;
}
