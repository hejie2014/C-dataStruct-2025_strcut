#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
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
void push(Node **top, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}
int pop(Node **top)
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
    int value = temp->data;
    *top = (*top)->next;
    free(temp);
    return value;
}
int topValue(Node *top)
{
    if (top == NULL)
    {
        return '\0'; // 空栈，返回空字符
    }
    return top->data;
}
bool isEmpty(Node *top)
{
    return top == NULL;
}
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
    if (*top == NULL)
    {
        printf("the stack is empty!\n");
        return;
    }
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
bool isNumericDigit(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z');
}
bool hasHigherPrec(char top, char c)
{
    if (top == '*' || top == '/')
        return true;
    else if ((top == '+' || top == '-') && (c == '+' || c == '-'))
        return true;
    return false;
}
bool isOpeningParentheses(char c)
{
    return c == '(' || c == '{' || c == '[';
}
bool isClosingParentheses(char c)
{
    return c == ')' || c == '}' || c == ']';
}
char *infixToPostfix(char *exp)
{
    Node *top = NULL;
    int number = strlen(exp);
    char *result = malloc(sizeof(char) * 64); // 转化后的表达式
    int count = 0;                            // result下标计数
    for (int i = 0; i < number; i++)
    {
        if (isNumericDigit(exp[i]))
        {
            result[count] = exp[i];
            count++;
        }
        else if (isOpeningParentheses(exp[i]))
        {
            push(&top, exp[i]);
        }
        else if (isClosingParentheses(exp[i]))
        {
            while (!isEmpty(top) && !isOpeningParentheses(topValue(top)))
            {
                result[count] = pop(&top);
                count++;
            }
            pop(&top);
        }
        else if (isOperator(exp[i]))
        { // 当栈顶元素是 " ( "，将其当做一个新的栈，也就是空栈，这时需要push,而不是直接加在表达式后面。
            // 当栈顶元素是 " ( "，我们先要计算这一部分，所以把它当做空栈。
            /*
            在你当前的 hasHigherPrec 实现下，去掉 !isOpeningParentheses(topValue(top)) 通常不会立刻出错：hasHigherPrec('(', c) 会返回 false，循环不会弹出 '('。
        但显式检查更安全且更清晰：它防止未来改动 hasHigherPrec 或意外把 '(' 当成操作符时导致把 '(' 弹出，从而破坏括号匹配。
            */
            while (!isEmpty(top) && !isOpeningParentheses((char)topValue(top)) // 先排除 '(' 等
                   && hasHigherPrec((char)topValue(top), exp[i]))              // 再比较优先级)
            {
                result[count] = pop(&top);
                count++;
            }
            push(&top, exp[i]);
        }
    }
    while (!isEmpty(top))
    {
        result[count] = pop(&top);
        count++;
    }
    result[count] = '\0';
    return result;
}

int main()
{
    Node *top = NULL;
    printf("d = %d", isNumericDigit('A'));
    // char exp[] = "2+3*4-5*6";
    // char exp[] = "((A+B)*C-D)*E";
    // char exp[] = "A*(B+C)";
    char exp[] = "A*(B+C*D)";
    char *res = infixToPostfix(exp);
    printf("res = %s", res);
    free(res);
    // printf("%d", hasHigherPrec('+', '-'));
    // printf("%d", hasHigherPrec('+', '+'));
    // printf("%d", hasHigherPrec('+', '*'));
    // printf("%d", hasHigherPrec('+', '/'));
    // printf("%d", hasHigherPrec('-', '-'));
    // printf("%d", hasHigherPrec('-', '+'));
    // printf("%d", hasHigherPrec('-', '*'));
    // pop(&top);
    // freeList(&top);
    // printf("value = %c", topValue(top));
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

bool IsOperand(char C)
{
    if (C >= '0' && C <= '9')
        return true;
    if (C >= 'a' && C <= 'z')
        return true;
    if (C >= 'A' && C <= 'Z')
        return true;
    return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$')
        return true;

    return false;
}

// Function to verify whether an operator is right associative or not.
// 用于验证一个运算符是否为右结合的函数。
int IsRightAssociative(char op)
{
    if (op == '$') // 乘方是右结合的 如： 2^3^2 = 2^9 =512
        return true;
    return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
// 用于获取运算符权重的函数。权重越高的运算符优先级越高。
int GetOperatorWeight(char op)
{
    int weight = -1;
    switch (op)
    {
    case '+':
    case '-':
        weight = 1;
    case '*':
    case '/':
        weight = 2;
    case '$':
        weight = 3;
    }
    return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2)
{
    int op1Weight = GetOperatorWeight(op1);
    int op2Weight = GetOperatorWeight(op2);

    // If operators have equal precedence, return true if they are left associative.
    // return false, if right associative.
    // if operator is left-associative, left one should be given priority.
    // 如果运算符具有相同的优先级，若它们是左结合的，则返回 true。  若为右结合的，则返回 false。 如果运算符是左结合的，则应优先处理左边的运算符。
    if (op1Weight == op2Weight)
    { // 判断是否是右结合，如果是，那么exp[i]优先级高于top,压栈。不是(返回true)，那么exp[i]优先级低于top,出栈
        if (IsRightAssociative(op1))
            return false;
        else
            return true;
    }
    // 正常判断优先级
    return op1Weight > op2Weight ? true : false;
}
/*
string InfixToPostfix(string expression)
{
    // Declaring a Stack from Standard template library in C++.
    stack<char> S;
    string postfix = ""; // Initialize postfix as empty string.
    for (int i = 0; i < expression.length(); i++)
    {

        // Scanning each character from left.
        // If character is a delimitter, move on.
        if (expression[i] == ' ' || expression[i] == ',')
            continue;

        // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if (IsOperator(expression[i]))
        {
            while (!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(), expression[i]))
            {
                postfix += S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
        // Else if character is an operand
        else if (IsOperand(expression[i]))
        {
            postfix += expression[i];
        }

        else if (expression[i] == '(')
        {
            S.push(expression[i]);
        }

        else if (expression[i] == ')')
        {
            while (!S.empty() && S.top() != '(')
            {
                postfix += S.top();
                S.pop();
            }
            S.pop();
        }
    }

    while (!S.empty())
    {
        postfix += S.top();
        S.pop();
    }

    return postfix;
}

*/