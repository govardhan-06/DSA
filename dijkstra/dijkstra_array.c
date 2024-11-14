#include <stdio.h>
#include <limits.h>

#define MAX_NODES 100

// find the minimum distance vertex in the set of vertices
int minDistance(int dist[], int inSPT[], int numVertices)
{
    int min = INT_MAX, minIndex = -1;
    for (int v = 0; v < numVertices; v++)
    {
        if (inSPT[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int numVertices)
{
    int dist[MAX_NODES];
    int inSPT[MAX_NODES]; // SPT - Shortest path tree
    // whenever node is added to SPT, the value at that index position
    // in this array will be made to 1

    for (int i = 0; i < numVertices; i++)
    {
        dist[i] = INT_MAX;
        inSPT[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < numVertices; count++)
    {
        int u = minDistance(dist, inSPT, numVertices);
        inSPT[u] = 1;

        for (int v = 0; v < numVertices; v++)
        {
            if (!inSPT[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    for (int i = 0; i < numVertices; i++)
        printf("%d %d\n", i, dist[i]);
}

int main()
{
    int numVertices, numEdges;
    scanf("%d", &numVertices);
    scanf("%d", &numEdges);
    int graph[MAX_NODES][MAX_NODES] = {0};

    for (int i = 0; i < numEdges; i++)
    {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }

    int src, dest;

    scanf("%d", &src);
    scanf("%d", &dest);

    dijkstra(graph, src, numVertices);
}