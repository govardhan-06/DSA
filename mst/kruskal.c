#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Edge structure to store source, destination, and weight of each edge
struct Edge
{
    int source, destination, weight;
};

// Comparator function for qsort to sort edges by weight
int compareEdges(const void *a, const void *b)
{
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->weight - edgeB->weight;
}

// Find function for Union-Find
int find(int parent[], int vertex)
{
    if (parent[vertex] != vertex)
    {
        parent[vertex] = find(parent, parent[vertex]);
    }
    return parent[vertex];
}

// Union function for Union-Find
void unionSets(int parent[], int rank[], int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rootX != rootY)
    {
        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Kruskal's Algorithm function
void kruskal(struct Edge edges[], int V, int E, int budget)
{
    int parent[MAX], rank[MAX];
    int mstWeight = 0;
    int edgesUsed = 0;

    // Initialize Union-Find structures
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort all edges in increasing order of weight
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    for (int i = 0; i < E && edgesUsed < V - 1; i++)
    {
        int u = edges[i].source;
        int v = edges[i].destination;
        int weight = edges[i].weight;

        // Find the roots of the source and destination
        int rootU = find(parent, u);
        int rootV = find(parent, v);

        // Check if including this edge would form a cycle
        if (rootU != rootV)
        {
            // Check if adding this edge would stay within the budget
            if (mstWeight + weight <= budget)
            {
                mstWeight += weight;
                edgesUsed++;
                unionSets(parent, rank, rootU, rootV);
            }
            else
            {
                break;
            }
        }
    }

    // Check if we found a valid MST within budget
    if (edgesUsed == V - 1)
    {
        printf("Minimum Cost Spanning Tree within the budget: %d\n", mstWeight);
    }
    else
    {
        printf("A valid MST within the budget is not possible.\n");
    }
}

// Main function to take input and call Kruskal's algorithm
int main()
{
    int V, E, budget;
    printf("Enter number of vertices, edges, and budget: ");
    scanf("%d %d %d", &V, &E, &budget);

    struct Edge edges[MAX];

    printf("Enter each edge in the format: source destination weight\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i].source, &edges[i].destination, &edges[i].weight);
        edges[i].source--;      // Adjust to zero-based index
        edges[i].destination--; // Adjust to zero-based index
    }

    kruskal(edges, V, E, budget);

    return 0;
}
