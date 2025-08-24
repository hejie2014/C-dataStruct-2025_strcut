#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 5
// top记录数组的下标；
bool isEmpty(int *top);
void Push(int **array, int x, int *top)
{
    if (*top == MAX_SIZE - 1) // MAX_SIZE - 1到达数组最后一个位置
    {
        // 需要扩展数组
        int *newArray = (int *)realloc(*array, sizeof(**array) * MAX_SIZE * 2);
        if (newArray == NULL)
        {
            printf("Memory allocation failed\n");
            free(*array); // 这里也可以不释放原数组，由主函数决定是否释放；
            return;
        }
        // 复制原数组内容到新数组
        // free(*array); 不能再释放原数组
        *array = newArray;
        printf("数组已经扩展\n");
        printf("Array resized to %d\n", MAX_SIZE * 2);
    }
    // top++;
    // A[top] = x
    (*array)[++(*top)] = x; // top先加1， 在A[top]赋值x
}
void Pop(int *top)
{                     // 判断数组是否为空
    if (isEmpty(top)) // top就是一个地址
    {
        printf("Error: No element to pop!\n");
        return;
    }
    (*top)--;
}
int Pop2(int *array, int *top)
{                     // 判断数组是否为空
    if (isEmpty(top)) // top就是一个地址
    {
        printf("Error: No element to pop!\n");
        return -1;
    }
    (*top)--;
    return array[*top + 1];
}
int Top(int *array, int *top)
{
    return array[*top];
}
bool isEmpty(int *top)
{
    // if (*top == -1)
    //     return true;
    // return false;
    return (*top == -1);
}
void Print(int *array, int *top)
{
    printf("stack: \n");
    for (int i = 0; i <= *top; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main()
{
    int top = -1; // top为-1表示数据为空
    int *array = (int *)malloc(sizeof(*array) * MAX_SIZE);
    if (array == NULL)
    {
        printf("Memory allocation failed\n");
        return 1; // 返回非零值表示错误
    }
    Push(&array, 2, &top);
    Print(array, &top);
    Push(&array, 3, &top);
    Print(array, &top);
    Push(&array, 4, &top);
    Print(array, &top);
    Push(&array, 5, &top);
    Print(array, &top);
    Push(&array, 6, &top);
    Print(array, &top);
    printf("--------------\n");
    Push(&array, 10, &top);
    Print(array, &top);
    printf("%d ", Top(array, &top));
    printf("\npop = %d ", Pop2(array, &top));
    Print(array, &top);

    free(array);  // 释放动态分配的内存
    array = NULL; // 避免悬空指针
    return 0;
}

/*
这段代码实现了一个基于动态数组的栈结构。主要功能包括入栈（Push）、出栈（Pop和Pop2）、获取栈顶元素（Top）、判断栈是否为空（isEmpty）以及打印栈内容（Print）。
 代码分析：
 1. 栈的初始大小是MAX_SIZE（5），当栈满时，通过realloc将数组大小扩展为原来的两倍。
 2. 使用top变量（初始为-1）来指示栈顶位置。
 3. Push函数：如果栈满，则扩展数组，然后将元素x放入栈顶。
 4. Pop函数：有两个版本，一个无返回值（Pop），另一个返回弹出的元素（Pop2）。
 5. Top函数返回栈顶元素。
 6. isEmpty判断栈是否为空。
 7. Print函数打印栈中所有元素。
 存在的问题：
 1. 在Push函数中，当realloc失败时，会free原数组，然后直接返回。这会导致内存泄漏，因为主函数中的array指针可能已经指向被释放的内存，而且后续的操作可能会继续使用这个已释放的指针。
 2. 在Pop2函数中，如果栈为空，返回-1。但-1可能是一个有效的数据，这样设计不利于错误处理。可以考虑通过返回一个状态码，或者使用额外的输出参数来返回元素值。
 3. 扩展数组时，代码中使用了MAX_SIZE*2，但是MAX_SIZE是初始大小，扩展后应该记录当前容量，而不是一直用初始的MAX_SIZE。否则，再次扩展时（比如连续 push 超过10个元素）就会出错，因为代码中只扩展了一次，但再次满时不会再次扩展（因为判断条件仍然是MAX_SIZE-1，而实际上容量已经扩大了）。
 4. 全局使用MAX_SIZE，但栈的容量已经改变后，判断条件没有更新，所以再次达到新的容量时不会再次扩展。
 5. 在Push函数中，realloc成功后，没有更新容量变量（代码中没有记录当前容量的变量），所以无法进行正确的扩容判断。
 优化建议：
 1. 使用一个结构体来管理栈，包括动态数组的指针、栈顶索引和当前容量。
 2. 这样，在Push时，可以根据当前容量和栈顶索引判断是否需要扩容，并且扩容后更新容量。
 3. 在realloc失败时，不要立即free原数组，因为原数组仍然有效。应该保持原数组不变，并报告错误。
 4. 考虑在Pop2函数中，使用指针参数来返回元素值，而函数本身返回一个状态表示成功或失败。
 重构代码：
 我们可以定义一个栈结构体，如下：
 typedef struct {
     int *data;
     int top;
     int capacity;
 } Stack;
 然后，提供一系列函数来操作这个栈，例如：初始化栈、销毁栈、入栈、出栈等。
 由于原代码是使用纯数组和单独的参数来管理栈的，所以我们可以考虑用结构体来封装，这样更易于管理。
 但是，原题要求是优化代码，所以我们可以根据原代码的风格进行优化，或者重构为结构体的方式。
 鉴于原代码中没有使用结构体，而且主函数中使用了单独的top和array变量，我们可以选择保持原代码风格，但修复扩容问题。
 然而，为了更清晰地管理栈的状态（当前容量），我们必须记录当前分配的数组大小。因此，我们可以在主函数中增加一个变量capacity，并传递其地址给Push函数，以便在Push函数中修改容量。
 另一种方法是使用结构体，这样更符合模块化设计。
 考虑到代码的清晰性和可维护性，我建议使用结构体重构。
 但是，如果要求保持原函数接口不变，则可能需要传递更多参数（如当前容量和新的容量）。
 由于原代码中已经出现了问题，且原代码的扩展逻辑有误（只能扩展一次），我决定用结构体重构。
 步骤：
 1. 定义Stack结构体。
 2. 编写初始化栈的函数。
 3. 编写销毁栈的函数（释放内存）。
 4. 修改Push和Pop函数，使其作用于Stack对象。
 5. 修改main函数，使用Stack对象。
 重构后的代码将更清晰，并且容易管理。
 由于原代码中Pop有两个版本，我们保留一个Pop函数，使其同时返回是否成功，并通过指针参数返回弹出的值。
 但是，为了保持简单，我们也可以让Pop函数返回弹出的值，并通过返回值表示成功与否（或者用另一个函数），但这样会改变接口。
  Alternatively, we can have Pop function that returns the popped value and have a separate function to check for emptiness. But then we cannot return an error code when popping from an empty stack.
 考虑到原代码中Pop2返回弹出的值，如果栈为空则返回-1，我们可以保留这种方式，但这样无法区分是错误还是正常返回-1。
 因此，我们改为使用指针参数来返回弹出的值，函数返回bool表示成功与否。
 或者，我们也可以让Pop函数不返回弹出的值，而是通过Top函数先获取栈顶元素，再Pop。这样，用户需要先调用Top，再调用Pop（Pop不返回元素），但这样容易出错（因为Top之后栈顶元素可能被修改）。
 另一种常见做法是：Pop函数返回弹出的元素，并通过异常或错误码来处理空栈。由于C语言没有异常，我们可以返回一个错误码，而元素通过指针参数返回。
 为了保持与原代码的相似性，我们这里不改变Pop2的接口，即Pop2返回弹出的元素，如果栈为空则返回-1，并打印错误信息。
 但是，这样无法处理栈中存储-1的情况。因此，我们重构时，将Pop函数改为返回bool，并通过指针参数返回元素。
 由于原代码中主函数使用了Pop2，我们这里改为使用新的Pop函数（通过指针参数返回元素）。
 但是，为了不改变原代码的测试逻辑，我们也可以保留Pop2，但注明其缺陷。
 鉴于原代码的主要问题是扩容，我们首先解决扩容问题，然后考虑错误处理。
 由于时间关系，我决定先修复扩容问题，而不改用结构体。我们可以通过传递当前容量的地址来更新容量。
 修改思路：
 1. 在main函数中，我们不再使用固定的MAX_SIZE，而是用一个变量capacity来记录当前容量，初始为MAX_SIZE。
 2. 将capacity的地址传递给Push函数，这样Push函数可以知道当前容量，并在需要时更新容量。
 3. 在Push函数中，判断top是否等于capacity-1，如果相等，则扩容为原来的2倍，并更新capacity。
 这样，我们就可以多次扩容了。
 同时，在realloc失败时，我们不应该free原数组，因为原数组还需要使用。而是打印错误信息并返回，保持栈不变。
 修改后的Push函数：
 void Push(int **array, int x, int *top, int *capacity)
 {
     if (*top == *capacity - 1) {
         int new_capacity = *capacity * 2;
         int *newArray = (int *)realloc(*array, sizeof(int) * new_capacity);
         if (newArray == NULL) {
             printf("Memory allocation failed\n");
             return; // 不改变原数组
         }
         *array = newArray;
         *capacity = new_capacity;
         printf("数组已经扩展\n");
         printf("Array resized to %d\n", new_capacity);
     }
     (*array)[++(*top)] = x;
 }
 然后，修改main函数，增加一个变量capacity，并初始化为MAX_SIZE，在调用Push时传递&capacity。
 同时，Pop2函数不需要改变，因为它不涉及容量。
 但是，这样修改后，Print函数和Top函数不需要改变，因为它们只使用array和top。
 注意：在main函数最后，释放array时，我们只需要free(array)，因为array指向的是最初分配的内存，realloc可能会改变其位置，但最后free会释放最后分配的内存块。


*/