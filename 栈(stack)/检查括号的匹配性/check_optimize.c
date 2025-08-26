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
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Node **top, char data)
{
    Node *newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}

bool pop(Node **top)
{
    if (*top == NULL)
    {
        return false; // 空栈，弹出失败
    }
    Node *temp = *top;
    *top = (*top)->next;
    free(temp);
    return true;
}
void pop2(Node **top)
{
    if (*top == NULL)
    {
        // 在括号匹配函数中，我们已经确保不会在空栈上pop，所以这里可以改为更严格的处理，比如退出程序
        fprintf(stderr, "pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = *top;
    *top = (*top)->next;
    free(temp);
}

char topValue(Node *top)
{
    if (top == NULL)
    {
        return '\0'; // 空栈，返回空字符
    }
    return top->data;
}
char topValue2(Node *top)
{
    if (top == NULL)
    {
        fprintf(stderr, "topValue from empty stack\n");
        exit(EXIT_FAILURE);
    }
    return top->data;
}
bool isEmpty(Node *top)
{
    return top == NULL;
}

void freeList(Node **top)
{
    Node *current = *top;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    *top = NULL;
}

bool isPair(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
           (opening == '[' && closing == ']') ||
           (opening == '{' && closing == '}');
}

bool checkBalanceParentheses(char *exp)
{
    Node *top = NULL;
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '[' || exp[i] == '(' || exp[i] == '{')
        {
            push(&top, exp[i]);
        }
        else if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']')
        {
            if (isEmpty(top) || !isPair(topValue2(top), exp[i]))
            {
                freeList(&top);
                return false;
            }
            pop2(&top);
        }
    }
    bool result = isEmpty(top);
    freeList(&top);
    return result;
}

int main()
{
    // 测试栈操作
    Node *top = NULL;
    push(&top, '(');
    push(&top, '2');
    push(&top, '+');
    push(&top, '3');
    push(&top, ')');
    freeList(&top);

    // 测试括号匹配
    char exp[] = "{[(2 + 3) + (2 + 1]]}";
    bool isBalanced = checkBalanceParentheses(exp);
    printf("Whether the expression matches: %s\n", isBalanced ? "yes" : "NO");

    return 0;
}