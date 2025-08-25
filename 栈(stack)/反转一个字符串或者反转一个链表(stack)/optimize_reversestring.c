#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 20

// 定义栈结构
typedef struct
{
    char *array;
    int top;
    int capacity;
} Stack;

// 判断栈是否为空
bool isEmpty(Stack *stack)
{
    return stack->top == -1;
}

// 判断栈是否已满
bool isFull(Stack *s)
{
    return s->top == s->capacity - 1;
}

// 压入元素
bool push(Stack *s, char x)
{
    if (isFull(s))
    {
        int new_capacity = s->capacity * 2;
        char *new_array = realloc(s->array, sizeof(char) * new_capacity);
        if (new_array == NULL)
        {
            printf("Memory allocation failed\n");
            return false;
        }
        s->array = new_array;
        s->capacity = new_capacity;
        printf("Array resized to %d\n", new_capacity);
    }
    s->array[++(s->top)] = x;
    return true;
}

// 弹出元素
bool pop(Stack *s, char *value)
{
    if (isEmpty(s))
    {
        printf("Error: No element to pop!\n");
        return false;
    }
    if (value != NULL)
    {
        *value = s->array[s->top];
    }
    s->top--;
    return true;
}

// 获取栈顶元素
bool topValue(Stack *s, char *value)
{
    if (isEmpty(s))
    {
        printf("The stack is empty!\n");
        return false;
    }
    *value = s->array[s->top];
    return true;
}

// 打印栈内容
void Print(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%c ", s->array[i]);
    }
    printf("\n");
}

// 栈的初始化
bool initStack(Stack *s, int capacity)
{
    s->array = malloc(sizeof(char) * capacity);
    if (s->array == NULL)
    {
        printf("Memory allocation failed\n");
        return false;
    }
    s->top = -1;
    s->capacity = capacity;
    return true;
}

// 释放栈
void freeStack(Stack *s)
{
    free(s->array);
    s->array = NULL;
    s->top = -1;
    s->capacity = 0;
}

// 反转字符串（使用栈但不修改原栈）
void Reverse(Stack *s, int n, char *C)
{
    // 保存原始栈状态
    int original_top = s->top;

    // 压入所有字符
    for (int i = 0; i < n; i++)
    {
        push(s, C[i]);
    }

    // 弹出所有字符到原数组（实现反转）
    for (int i = 0; i < n; i++)
    {
        char value;
        pop(s, &value);
        C[i] = value;
    }

    // 恢复栈状态
    s->top = original_top;
}

// 专门用于反转字符串的函数（不修改栈状态）
void ReverseString(Stack *s, char *str)
{
    int len = strlen(str);

    // 压入所有字符
    for (int i = 0; i < len; i++)
    {
        push(s, str[i]);
    }

    // 弹出所有字符到原数组（实现反转）
    for (int i = 0; i < len; i++)
    {
        pop(s, &str[i]);
    }
}

int main()
{
    Stack s;
    if (!initStack(&s, INITIAL_CAPACITY))
    {
        return 1;
    }

    // 测试1: 使用Reverse函数
    char C[] = "hello";
    printf("Original string: %s\n", C);

    int number = strlen(C);
    printf("String length: %d \n", number);

    Reverse(&s, number, C);
    printf("Reversed string: %s\n", C);
    printf(" s.array[0] = %c\n", s.array[0]);
    // 打印栈状态（应该为空）
    Print(&s);

    // 测试2: 使用ReverseString函数
    char D[] = "world";
    printf("\nOriginal string: %s\n", D);
    ReverseString(&s, D);
    printf("Reversed string: %s\n", D);

    // 打印栈状态（应该为空）
    Print(&s);

    // 测试栈操作
    printf("\nTesting stack operations:\n");
    push(&s, 'a');
    push(&s, 'b');
    push(&s, 'c');
    Print(&s);

    char topChar;
    if (topValue(&s, &topChar))
    {
        printf("Top value: %c\n", topChar);
    }

    char poppedChar;
    while (pop(&s, &poppedChar))
    {
        printf("Popped: %c\n", poppedChar);
    }

    // 尝试从空栈弹出
    pop(&s, NULL);

    freeStack(&s);
    return 0;
}