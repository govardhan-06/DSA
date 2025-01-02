#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Graph
{
    int V;
    int **adj;
};

void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    graph->adj[src][dest] = weight;
    graph->adj[dest][src] = weight;
}

int minDistance(const int dist[], const int inSPT[], int numVertices)
{
    int min = INT_MAX;
    int minIndex = -1;
    for (int v = 0; v < numVertices; v++)
    {
        if (!inSPT[v] && dist[v] < min)
        {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijsktra(struct Graph *graph, int src, int dist[])
{
    int inSPT[graph->V];
    for (int i = 0; i < graph->V; i++)
    {
        dist[i] = INT_MAX;
        inSPT[i] = 0;
    }
    dist[src] = 0;
    for (int count = 0; count < graph->V; count++)
    {
        int u = minDistance(dist, inSPT, graph->V);
        inSPT[u] = 1;

        for (int v = 0; v < graph->V; v++)
        {
            if (!inSPT[v] && graph->adj[u][v] && dist[u] != INT_MAX && dist[v] > dist[u] + graph->adj[u][v])
            {
                dist[v] = dist[u] + graph->adj[u][v];
            }
        }
    }
}

int main()
{
    int V, E;
    scanf("%d", &V);
    scanf("%d", &E);
    struct Graph *graph;
    graph->V = V;
    graph->adj = (int **)malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++)
    {
        graph->adj[i] = (int *)malloc(V * sizeof(int));
        for (int v = 0; v < V; v++)
        {
            graph->adj[i][v] = 0;
        }
    }

    for (int i = 0; i < E; i++)
    {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    int src;
    scanf("%d", &src);
    int *shortDistance = (int *)malloc(V * sizeof(int));
    dijsktra(graph, src, shortDistance);

    for (int i = 0; i < V; i++)
    {
        printf("%d ", shortDistance[i]);
    }
    printf("\n");

    free(shortDistance);

    for (int i = 0; i < V; i++)
    {
        free(graph->adj[i]);
    }
    free(graph->adj);

    return 0;
}