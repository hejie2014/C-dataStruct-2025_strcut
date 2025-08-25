#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 前置声明：告诉编译器Stack是一个结构体类型，具体定义在后面
typedef struct Stack Stack;

// 定义函数指针类型：这些类型描述了Stack结构体中将包含的方法签名
typedef void (*PushFunc)(Stack *, int); // 压栈方法类型
typedef void (*PopFunc)(Stack *);       // 出栈方法类型
typedef int (*TopValueFunc)(Stack *);   // 获取栈顶元素方法类型
typedef bool (*IsEmptyFunc)(Stack *);   // 检查栈是否为空方法类型
typedef void (*PrintFunc)(Stack *);     // 打印栈内容方法类型
typedef void (*FreeFunc)(Stack *);      // 释放栈内存方法类型

// 栈节点的结构定义（嵌套在Stack结构体中）
struct Node
{
    int data;          // 节点存储的数据
    struct Node *next; // 指向下一个节点的指针
};

// 栈结构体的完整定义
struct Stack
{
    // 数据成员
    struct Node *top; // 指向栈顶节点的指针

    // 方法成员（函数指针）
    PushFunc push;         // 压栈方法
    PopFunc pop;           // 出栈方法
    TopValueFunc topValue; // 获取栈顶元素方法
    IsEmptyFunc isEmpty;   // 检查栈是否为空方法
    PrintFunc print;       // 打印栈内容方法
    FreeFunc free;         // 释放栈内存方法
};

// ========== 方法实现 ==========

// 压栈方法的实现
void pushImpl(Stack *self, int data)
{
    // 创建新节点
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = data;      // 设置节点数据
    temp->next = self->top; // 新节点指向原栈顶
    self->top = temp;       // 更新栈顶指针为新节点
}

// 出栈方法的实现
void popImpl(Stack *self)
{
    if (self->top == NULL)
    {
        printf("The stack is empty! Cannot pop.\n");
        return;
    }
    struct Node *temp = self->top; // 保存原栈顶节点
    self->top = self->top->next;   // 更新栈顶指针为下一个节点
    free(temp);                    // 释放原栈顶节点的内存
}

// 获取栈顶元素方法的实现
int topValueImpl(Stack *self)
{
    if (self->top == NULL)
    {
        printf("The stack is empty! No top value.\n");
        return -1; // 返回错误码
    }
    return self->top->data; // 返回栈顶节点的数据
}

// 检查栈是否为空方法的实现
bool isEmptyImpl(Stack *self)
{
    return (self->top == NULL); // 如果栈顶指针为NULL，栈为空
}

// 打印栈内容方法的实现
void printImpl(Stack *self)
{
    struct Node *temp = self->top; // 从栈顶开始遍历
    printf("Stack: ");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data); // 打印当前节点数据
        temp = temp->next;            // 移动到下一个节点
    }
    printf("NULL\n"); // 表示链表结束
}

// 释放栈内存方法的实现
void freeImpl(Stack *self)
{
    // 循环弹出所有节点，直到栈为空
    while (self->top != NULL)
    {
        popImpl(self); // 使用pop方法释放每个节点
    }
    free(self); // 最后释放Stack结构体本身的内存
}

// ========== 栈的构造函数 ==========
Stack *createStack()
{
    // 分配Stack结构体的内存
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    // 初始化数据成员
    stack->top = NULL; // 初始时栈为空

    // 绑定方法：将函数指针指向具体的实现函数
    stack->push = pushImpl;
    stack->pop = popImpl;
    stack->topValue = topValueImpl;
    stack->isEmpty = isEmptyImpl;
    stack->print = printImpl;
    stack->free = freeImpl;

    return stack; // 返回创建的栈对象
}

// ========== 主函数：示例使用 ==========
int main()
{
    // 创建栈对象
    Stack *stack = createStack();

    // 使用栈对象的方法
    printf("Is stack empty? %s\n", stack->isEmpty(stack) ? "Yes" : "No");

    // 压入一些数据
    stack->push(stack, 10);
    stack->push(stack, 20);
    stack->push(stack, 30);

    // 打印栈内容
    stack->print(stack);

    // 获取并打印栈顶元素
    printf("Top value: %d\n", stack->topValue(stack));

    // 弹出一个元素
    stack->pop(stack);

    // 再次打印栈内容
    stack->print(stack);

    // 释放栈内存
    stack->free(stack);

    return 0;
}