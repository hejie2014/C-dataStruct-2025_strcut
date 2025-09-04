#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct
{
    int numVertices;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

// 初始化图
void initGraph(Graph *graph, int vertices)
{
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

// 添加边（无向图）
void addEdge(Graph *graph, int src, int dest)
{
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices)
    {
        graph->adjacencyMatrix[src][dest] = 1;
        graph->adjacencyMatrix[dest][src] = 1; // 无向图需要对称设置
    }
}

// 添加带权边
void addWeightedEdge(Graph *graph, int src, int dest, int weight)
{
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices)
    {
        graph->adjacencyMatrix[src][dest] = weight;
        graph->adjacencyMatrix[dest][src] = weight; // 无向图
    }
}

// 打印图
void printGraph(Graph *graph)
{
    printf("邻接矩阵:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    Graph graph;
    int vertices = 5;

    // 初始化图
    initGraph(&graph, vertices);

    // 添加边
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 4);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 1, 4);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);

    // 打印图
    printGraph(&graph);

    return 0;
}