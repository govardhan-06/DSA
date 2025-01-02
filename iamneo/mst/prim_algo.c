#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Graph
{
    int numVertices;
    int **adjMatrix;
};

void createGraph(struct Graph *graph, int numVertices)
{
    graph->numVertices = numVertices;
    graph->adjMatrix = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; i++)
    {
        graph->adjMatrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++)
        {
            graph->adjMatrix[i][j] = 0; // Initialize matrix with 0 (no edges)
        }
    }
}

void addEdge(struct Graph *graph, int src, int dest, int weight)
{
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight; // For undirected graph
}

int minWeightVertex(int *weights, int *inMST, int numVertices)
{
    int min = INT_MAX, minIndex = -1;
    for (int v = 0; v < numVertices; v++)
    {
        if (inMST[v] == 0 && weights[v] < min)
        {
            min = weights[v];
            minIndex = v;
        }
    }
    return minIndex;
}

int *primMST(struct Graph *graph, int *numMSTEdges)
{
    int *parent = (int *)malloc(graph->numVertices * sizeof(int));
    int *weights = (int *)malloc(graph->numVertices * sizeof(int));
    int *inMST = (int *)malloc(graph->numVertices * sizeof(int));

    for (int i = 0; i < graph->numVertices; i++)
    {
        weights[i] = INT_MAX;
        inMST[i] = 0;
    }

    parent[0] = -1;
    weights[0] = 0;

    for (int i = 0; i < graph->numVertices - 1; i++)
    {
        // Find the vertex with the minimum weight that is not yet included in MST
        int u = minWeightVertex(weights, inMST, graph->numVertices);
        inMST[u] = 1; // Mark vertex u as included in MST

        // Update the weights and parent for adjacent vertices
        for (int v = 0; v < graph->numVertices; v++)
        {
            if (graph->adjMatrix[u][v] && inMST[v] == 0 && graph->adjMatrix[u][v] < weights[v])
            {
                parent[v] = u;
                weights[v] = graph->adjMatrix[u][v];
            }
        }
    }

    *numMSTEdges = graph->numVertices - 1; // Number of edges in MST
    free(weights);
    free(inMST);
    return parent;
}

int existsPathWithLimit(struct Graph *graph, int src, int dest, int limit)
{
    int numMSTEdges;
    int *parent = primMST(graph, &numMSTEdges);

    int maxWeight = 0;
    int current = dest;
    while (current != src && parent[current] != -1)
    {
        int p = parent[current];
        if (graph->adjMatrix[current][p] > maxWeight)
        {
            maxWeight = graph->adjMatrix[current][p];
        }
        current = p;
    }

    free(parent);
    return maxWeight <= limit;
}

int main()
{
    int numVertices;
    scanf("%d", &numVertices);
    int numEdges;
    scanf("%d", &numEdges);
    struct Graph graph;
    createGraph(&graph, numVertices);

    for (int i = 0; i < numEdges; i++)
    {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(&graph, src, dest, weight);
    }

    int numQueries;
    scanf("%d", &numQueries);
    for (int i = 0; i < numQueries; i++)
    {
        int source, destination, limit;
        scanf("%d %d %d", &source, &destination, &limit);
        int existsPath = existsPathWithLimit(&graph, source, destination, limit);
        printf("Exists path between %d and %d with limit %d: %s\n", source, destination, limit,
               existsPath ? "true" : "false");
    }

    for (int i = 0; i < graph.numVertices; i++)
    {
        free(graph.adjMatrix[i]);
    }
    free(graph.adjMatrix);
    return 0;
}
