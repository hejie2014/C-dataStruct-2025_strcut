#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 5

typedef struct
{
    int *data;
    int top;
    int capacity;
} Stack;

bool isEmpty(Stack *s)
{
    return s->top == -1;
}

void push(Stack *s, int x)
{
    if (s->top == s->capacity - 1)
    {
        int new_capacity = s->capacity * 2;
        int *new_data = realloc(s->data, sizeof(int) * new_capacity);
        if (new_data == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }
        s->data = new_data;
        s->capacity = new_capacity;
        printf("Array resized to %d\n", new_capacity);
    }
    s->data[++s->top] = x;
}

bool pop(Stack *s, int *value)
{
    if (isEmpty(s))
    {
        printf("Error: No element to pop!\n");
        return false;
    }
    *value = s->data[s->top--];
    return true;
}

int top(Stack *s)
{
    return s->data[s->top];
}

void print(Stack *s)
{
    printf("Stack: ");
    for (int i = 0; i <= s->top; i++)
    {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

void initStack(Stack *s, int capacity)
{
    s->data = malloc(sizeof(int) * capacity);
    if (s->data == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    s->top = -1;
    s->capacity = capacity;
}

void freeStack(Stack *s)
{
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

int main()
{
    Stack s;
    initStack(&s, INITIAL_CAPACITY);

    push(&s, 2);
    print(&s);
    push(&s, 3);
    print(&s);
    push(&s, 4);
    print(&s);
    push(&s, 5);
    print(&s);
    push(&s, 6);
    print(&s);
    printf("--------------\n");
    push(&s, 10);
    print(&s);

    int val;
    if (pop(&s, &val))
    {
        printf("Popped: %d\n", val);
    }
    print(&s);

    freeStack(&s);
    return 0;
}