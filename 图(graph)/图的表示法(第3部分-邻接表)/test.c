#include <stdio.h>
#include <stdlib.h>

// 邻接表中的节点
struct AdjListNode
{
    int dest;
    int weight; // 用于带权图
    struct AdjListNode *next;
};

// 邻接表
struct AdjList
{
    struct AdjListNode *head;
};

// 图结构
struct Graph
{
    int numVertices;
    struct AdjList *array;
};

// 创建新的邻接表节点
struct AdjListNode *newAdjListNode(int dest, int weight)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// 创建图
struct Graph *createGraph(int vertices)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->array = (struct AdjList *)malloc(vertices * sizeof(struct AdjList));

    for (int i = 0; i < vertices; i++)
    {
        graph->array[i].head = NULL;
    }
    return graph;
}

// 添加边（无向图）
void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    // 从src到dest的边
    struct AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // 从dest到src的边（无向图）
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// 打印图
void printGraph(struct Graph *graph)
{
    printf("邻接表:\n");
    for (int v = 0; v < graph->numVertices; v++)
    {
        struct AdjListNode *pCrawl = graph->array[v].head;
        printf("顶点 %d: ", v);
        while (pCrawl)
        {
            printf("-> %d(权重:%d) ", pCrawl->dest, pCrawl->weight);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int main()
{
    int vertices = 5;
    struct Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 4, 3);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 1, 4, 4);
    addEdge(graph, 2, 3, 2);
    addEdge(graph, 3, 4, 1);

    printGraph(graph);

     return 0;
}