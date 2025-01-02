#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

struct Graph
{
    int visited[MAX_VERTICES];
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};

void addEdge(struct Graph *g, int v, int w)
{
    g->adjMatrix[v][w] = 1;
}

void DFS(struct Graph *g, int vertex)
{
    g->visited[vertex] = 1;
    printf("%d ", vertex);
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        if (g->adjMatrix[vertex][i] == 1 && !g->visited[i])
        {
            DFS(g, i);
        }
    }
}

int main()
{
    int n;
    int e;
    scanf("%d %d", &n, &e);
    struct Graph g = {0}; // Initialize all fields of g to 0
    for (int i = 0; i < e; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(&g, a, b);
    }
    int start;
    scanf("%d", &start);
    DFS(&g, start);

    return 0;
}