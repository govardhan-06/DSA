#include <stdio.h>
#include <stdlib.h>

struct Graph
{
    int *visited;
    int **adjList;
};

void addEdge(struct Graph *graph, int src, int dest)
{
    graph->adjList[src][dest] = 1;
    graph->adjList[dest][src] = 1;
}

void createGraph(struct Graph *graph, int numVertices)
{
    graph->visited = (int *)malloc(numVertices * sizeof(int));
    graph->adjList = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; i++)
    {
        graph->visited[i] = 0;
        graph->adjList[i] = (int *)malloc(numVertices * sizeof(int));
        for (int v = 0; v < numVertices; v++)
        {
            graph->adjList[i][v] = 0;
        }
    }
}

int bfs(struct Graph *graph, int numVertices, int search)
{
    if (search >= numVertices)
    {
        free(graph->adjList);
        free(graph->visited);
        return -1;
    }
    int *queue = (int *)malloc(numVertices * sizeof(int));
    int front = -1, rear = -1;
    queue[++rear] = 0;
    int level = 0;
    graph->visited[0] = 1;
    while (front != rear)
    {
        int currentNode = queue[++front];
        if (currentNode == search)
        {
            free(graph->adjList);
            free(graph->visited);
            free(queue);
            return level;
        }
        for (int neighbour = 0; neighbour < numVertices; neighbour++)
        {
            if (graph->adjList[currentNode][neighbour] && !graph->visited[neighbour])
            {
                queue[++rear] = neighbour;
                graph->visited[neighbour] = 1;
            }
        }
        level++;
    }
    return -1;
}

int main()
{
    int V, E;
    scanf("%d %d", &V, &E);
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    createGraph(graph, V);
    for (int i = 0; i < E; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
    int search;
    scanf("%d", &search);
    int level = bfs(graph, V, search);
    printf("%d", level);
}
