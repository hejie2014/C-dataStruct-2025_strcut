#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 邻接表的节点
typedef struct adjListNode
{
    int dest;
    int weight; // 用于带权图
    struct adjListNode *next;
} adjListNode;

// 使用一个结构体存储邻接表的头指针
typedef struct
{
    adjListNode *head;
} adjList;

typedef struct Graph
{
    int numVertices;
    adjList *array; // 使用一个数组array[]存储 所有邻接表的头指针；
} Graph;
// 创建新的邻接表节点, dest是边的end节点,weight: 权重
adjListNode *createListNode(int dest, int weight)
{
    adjListNode *newNode = malloc(sizeof(adjListNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // 赋值
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
Graph *createGrape(int vertices)
{
    Graph *graph = malloc(sizeof(Graph));
    if (graph == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    // 赋值
    graph->numVertices = vertices;
    // 动态分配一个数组；数组元素是邻接表结构体， 也就是指向邻接表头节点指针
    graph->array = malloc(sizeof(adjList) * vertices);
    if (graph->array == NULL)
    {
        printf("Memory allocation failed!\n");
        free(graph); // 释放之前分配的graph
        return NULL;
    }
    // 初始化头指针结构体，malloc分配的数据是垃圾值;
    for (int i = 0; i < vertices; i++)
    {
        graph->array[i].head = NULL; // graph->array[i]是adjList结构体
    }
    return graph;
}
// 添加边（无向图）
void addEdge(Graph *graph, int src, int dest, int weight)
{
    // 从src到dest的边
    adjListNode *newNode = createListNode(dest, weight);
    // 使用链表的头插法
    newNode->next = graph->array[src].head; // 新创建的节点指向头指针指向的节点
                                            // 更新头结点
    graph->array[src].head = newNode;

    // 从dest到src的边（无向图）相反操作，AB BA
    // 对graph->array[src].head不影响，可以指向其他地址
    newNode = createListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
// 打印图
void printGraph(Graph *graph)
{
    printf("邻接表:\n");
    for (int v = 0; v < graph->numVertices; v++)
    {
        adjListNode *headPtrList = graph->array[v].head;
        adjListNode *temp = headPtrList;
        printf("顶点 %d: ", v);
        if (headPtrList == NULL)
        {
            printf("NULL\n");
            continue;
        }
        while (headPtrList != NULL)
        {
            printf("%d(weight:%d)", headPtrList->dest, headPtrList->weight);
            if (headPtrList->next != NULL)
                printf(" -> ");
            headPtrList = headPtrList->next;
        }
        if (temp != NULL)
        {
            printf(" -> NULL\n");
            temp = NULL;
        }
    }
}
// 释放内存
void freeGraph(Graph *graph)
{ // graph是否为空
    if (graph == NULL)
        return;
    for (int i = 0; i < graph->numVertices; i++) // 遍历每个头指针
    {
        adjListNode *temp = graph->array[i].head;
        if (temp == NULL) // 指针为空，结束本次循环
        {
            printf("%d row is NULL\n", i);
            continue;
        }
        while (graph->array[i].head != NULL) // 释放链表的每一个节点
        {
            temp = graph->array[i].head;
            graph->array[i].head = graph->array[i].head->next;
            free(temp);
        }
        printf("%d row free\n", i);
    }
    printf("memory has been released\n");
}

int main()
{
    int vertices = 8;
    Graph *graph = createGrape(vertices);
    // 添加数据
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 4, 3);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 1, 4, 4);
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 3, 4, 1);

    printGraph(graph); // 打印数据

    freeGraph(graph);
    /*
    邻接表:
        顶点 0: 4(weight:3) -> 1(weight:2) -> NULL
        顶点 1: 4(weight:4) -> 3(weight:5) -> 2(weight:1) -> 0(weight:2) -> NULL
        顶点 2: 3(weight:2) -> 1(weight:1) -> NULL
        顶点 3: 4(weight:1) -> 2(weight:2) -> 1(weight:5) -> NULL
        顶点 4: 3(weight:1) -> 1(weight:4) -> 0(weight:3) -> NULL
        顶点 5: NULL
        顶点 6: NULL
        顶点 7: NULL
        0 row free
        1 row free
        2 row free
        3 row free
        4 row free
        5 row is NULL
        6 row is NULL
        7 row is NULL
    memory has been released
    */
    graph = NULL;
    return 0;
}