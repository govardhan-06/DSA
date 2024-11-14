#include <stdio.h>
#include <stdlib.h>

struct Graph
{
    int *visited;
    int **adj;
};

void addEdge(struct Graph *graph, int src, int dest)
{
    graph->adj[src][dest] = 1;
}

void DFS(struct Graph *graph, int src, int numVertices)
{
    graph->visited[src] = 1; // Mark current node as visited
    printf("%d ", src);      // Print the visited node

    // Visit all the adjacent nodes (neighbors)
    for (int i = 0; i < numVertices; i++)
    {
        if (graph->adj[src][i] == 1 && !graph->visited[i]) // Corrected condition
        {
            DFS(graph, i, numVertices); // Recursively visit unvisited neighbors
        }
    }
}

int main()
{
    int n, e;
    scanf("%d", &n); // Number of vertices
    scanf("%d", &e); // Number of edges

    // Allocate memory for the graph structure
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));

    // Allocate memory for visited array and adjacency matrix
    graph->visited = (int *)malloc(n * sizeof(int));
    graph->adj = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        graph->visited[i] = 0;                          // Initially mark all vertices as unvisited
        graph->adj[i] = (int *)malloc(n * sizeof(int)); // Allocate memory for adjacency row
        for (int v = 0; v < n; v++)
        {
            graph->adj[i][v] = 0; // Initialize adjacency matrix to 0 (no edges)
        }
    }

    // Read the edges and add them to the graph
    int v, w;
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d", &v, &w);
        addEdge(graph, v, w);
    }

    // Read the starting vertex for DFS
    int start;
    scanf("%d", &start);

    // Perform DFS starting from the 'start' vertex
    DFS(graph, start, n);

    // Free allocated memory
    for (int i = 0; i < n; i++)
    {
        free(graph->adj[i]); // Free each row of the adjacency matrix
    }
    free(graph->adj);     // Free the adjacency matrix pointer
    free(graph->visited); // Free the visited array
    free(graph);          // Free the graph structure

    return 0;
}
