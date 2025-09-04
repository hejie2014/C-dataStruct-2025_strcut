#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

typedef struct
{
    int numVertices;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;
// 初始化图

void initGraph(Graph *graph, int vertices)
{ // vertices参数是需要的顶点数量
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}
// 判断数据是否符合要求,sec,dest为下标，从0开始计数，numVertices，顶点数量
bool isTrueData(int sec, int dest, int numVertices)
{
    return (sec >= 0 && sec < numVertices && dest >= 0 && dest < numVertices);
}

// 添加边
void addEdge(Graph *graph, int sec, int dest)
{
    if (isTrueData(sec, dest, graph->numVertices))
    { // i 表示有连接 ， 0 表示无连接
        graph->adjacencyMatrix[sec][dest] = 1;
        graph->adjacencyMatrix[dest][sec] = 1; // 无向图需要对称设置
    }
}
// 添加带权边
void addWeightEdge(Graph *graph, int sec, int dest, int weight)
{
    if (isTrueData(sec, dest, graph->numVertices))
    { // 不是0，就是有连接，数值是权重
        graph->adjacencyMatrix[sec][dest] = weight;
        graph->adjacencyMatrix[dest][sec] = weight; // 无向图需要对称设置
    }
}

// 打印图
void printGraph(Graph *graph)
{
    printf("邻接矩阵:\n");
    printf("   ");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%c: ", 'A' + i);
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

    initGraph(&graph, vertices);
    // 添加边
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 4);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 1, 4);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);
    /*      0 1 2 3 4
            A B C D E
      0  A: 0 1 0 0 1
      1  B: 1 0 1 1 1
      2  C: 0 1 0 1 0
      3  D: 0 1 1 0 1
      4  E: 1 1 0 1 0
    */
    // 打印图
    printGraph(&graph);

    return 0;
}
