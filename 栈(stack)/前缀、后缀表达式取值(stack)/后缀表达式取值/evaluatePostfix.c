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
    newNode->next = *top;
    *top = newNode;
}
char pop(Node **top)
{
    Node *temp = *top;
    // if (*top == NULL)
    // {
    //     printf("The stack is empty! Cannot pop.\n");
    //     return -1;
    // }
    if (*top == NULL)
    {
        // 在括号匹配函数中，我们已经确保不会在空栈上pop，所以这里可以改为更严格的处理，比如退出程序
        fprintf(stderr, "pop from empty stack\n");
        exit(EXIT_FAILURE);
    }
    int charValue = temp->data;
    *top = (*top)->next;
    free(temp);
    return charValue;
}
char topValue(Node *top)
{
    if (top == NULL)
    {
        return '\0'; // 空栈，返回空字符
    }
    /*
    if (top == NULL)
    {
    fprintf(stderr, "topValue from empty stack\n");
    exit(EXIT_FAILURE);
    }
    */
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
// 判断操作符
bool isOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}
// 判断数字
bool isNumericDigit(char c)
{
    return (c >= '0' && c <= '9');
}
int calculate(char operator, int op1, int op2)
{
    int result = 0;
    switch (operator)
    {
    case '+':
        result = op1 + op2;
        break;
    case '-':
        result = op1 - op2;
        break;
    case '*':
        result = op1 * op2;
        break;
    case '/':
        if (op2 == 0)
        {
            printf("Error: Division by zero!分母不能为0!\n");
            return -1;
        }
        result = op1 / op2;
        break;
    default:
        printf("Invalid operation!\n");
        break;
    }
    return result;
}

int evaluatePostfix(char *exp)
{
    int number = strlen(exp);
    int result = 0;
    Node *top = NULL;
    for (int i = 0; i < number; i++)
    { /* if (exp[i] >= '0' && exp[i] <= '9')
             push(&top, exp[i] - '0'); // 把字符数字转为整数
         else
         {
             // 如果表达式包含多位数或空格分隔，需额外处理，这里只处理单个数字字符
         }*/
        // 遇到空格或者，就结束本次循环
        if (exp[i] == ' ' || exp[i] == ',')
            continue;
        else if (isNumericDigit(exp[i]))
        {
            int operand = 0;
            // 对于一个多位数，当我们从左向右扫描时。
            // 每次向右获取一个数字时，我们可以将操作数中的当前总和乘以 10 operand * 10 + (exp[i] - '0')
            // 并加上这个新数字。
            while (i < number && isNumericDigit(exp[i]))
            {
                operand = operand * 10 + (exp[i] - '0');
                i++;
            }
            // 最后，当 i 指向一个非数字字符或字符串末尾时，你将跳出 while 循环,将 i 减 1，因为在循环的递增部分它会再次递增。我们不想因为 i 递增两次而跳过非数字字符。
            i--;                 // 回退到上一个字符
            push(&top, operand); // 减去字符0， 得到具体 0-9的数字，而不是字符
        }
        else if (isOperator(exp[i]))
        {
            int op2 = pop(&top);
            int op1 = pop(&top);
            result = calculate(exp[i], op1, op2);
            push(&top, result);
        }
    }
    result = topValue(top);
    freeList(&top);
    return result;
}

int main()
{
    Node *top = NULL;
    char exp[] = "12 3*5 4*+9-"; //"23*54*+9-"
    int result = evaluatePostfix(exp);
    printf("result = %d\n", result);
    char a = '2' - '0';
    printf("%d", a);
    // int n = calculate('/', 3, 2);
    // printf("n = %d", n);
    // printf("Is stack empty after free? %s\n", isEmpty(top) ? "Yes" : "No");
    // pop(&top);
    // push(&top, '(');
    // push(&top, '2');
    // push(&top, '+');
    // push(&top, '3');
    // push(&top, ')');
    // Print(top);
    // pop(&top);
    // Print(top);
    // freeList(&top);

    return 0;
}