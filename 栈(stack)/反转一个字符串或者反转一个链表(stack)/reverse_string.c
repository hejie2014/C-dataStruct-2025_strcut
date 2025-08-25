#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INITIAL_CAPACITY 20

// 定义一个结构体，包括数组，栈顶指针和容量
typedef struct
{
    char *array;
    int top;
    int capacity;
} Stack;
// 判断数组是否为空
bool isEmpty(Stack *stack)
{
    return stack->top == -1; // 传入一个结构体指针
}
void push(Stack *s, char x)
{
    if (s->top == s->capacity - 1) // capacity - 1到达数组最后一个位置
    {
        int new_capacity = s->capacity * 2;
        char *new_array = realloc(s->array, sizeof(char) * new_capacity);
        if (new_array == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }
        s->array = new_array;
        s->capacity = new_capacity;
        printf("Array resized to %d\n", new_capacity);
    }
    s->array[++(s->top)] = x;
}
void pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Error: No element to pop!\n");
        return;
    }
    s->top--;
}
char topValue(Stack *s)
{
    if (s->top == -1)
    {
        printf("the stack is empty!\n");
        return -1;
    }
    return s->array[s->top];
}

void Print(Stack *s)
{
    printf("Stack: ");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%c ", s->array[i]);
    }
    printf("\n");
}
// 栈的初始化
void initStack(Stack *s, int capacity)
{
    s->array = malloc(sizeof(char) * capacity);
    if (s->array == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    s->top = -1;
    s->capacity = capacity;
}
// 释放栈
void freeStack(Stack *s)
{
    free(s->array);
    s->array = NULL;
    s->top = -1;
    s->capacity = 0;
}

void Reverse(Stack *s, int n, char *C)
{
    for (int i = 0; i < n; i++)
    {
        push(s, C[i]);
    }
    for (int i = 0; i < n; i++)
    {
        C[i] = topValue(s);
        pop(s);
    }
}

int main()
{
    Stack s;
    initStack(&s, INITIAL_CAPACITY);
    char C[] = "hello";
    /*
    短答：因为你写的是 char C[] = "hello"; —— 这会在栈/数据区创建一个可修改的字符数组，所以 C[0] = 'H'; 合法。
    如果是 char *C = "hello"; 那就是指向只读字符串字面量的指针，修改会产生未定义行为（可能崩溃）。
    说明与示例：
    char C[] = "hello"; // 可修改，内容为 ['h','e','l','l','o','\0']，sizeof(C) == 6
    char *C = "hello"; // 指向字面量（通常只读），不能写入
    */
    C[0] = 'H';
    int number = sizeof(C) / sizeof(C[0]) - 1;
    printf("%d \n", number);
    Reverse(&s, number, C);
    Print(&s); // stack并不为空，只是top为-1；
    freeStack(&s);
    for (int i = 0; i < number; i++)
    {
        printf("%c ", C[i]);
    }
    topValue(&s);
    /* int number = sizeof(s.array) / sizeof(s.array[0]);
    s.array 是 char *，所以 sizeof(s.array) 是指针大小（在 64-bit 系统通常为 8），sizeof(s.array[0]) 是 1，结果是 8。
    sizeof 无法得到动态分配内存里的元素个数 — 它只在编译时知道静态数组大小或运行时返回指针本身的字节数。
    */
    // int number = s.top + 1;
    // printf("%d \n", number);
    // Reverse(&s, number);
    // Print(&s);
    // freeStack(&s);
    // topValue(&s);
    // push(&s, 65);
    // Print(&s);
    // push(&s, 66);
    // Print(&s);
    // push(&s, 67);
    // Print(&s);
    // push(&s, 68);
    // Print(&s);
    // push(&s, 69);
    // Print(&s);
    // printf("--------------\n");
    // printf("top = %c", topValue(&s));
    // pop(&s);
    // Print(&s);

    return 0;
}
