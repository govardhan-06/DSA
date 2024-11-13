#include <stdio.h>
#include <stdlib.h>

struct Edge
{
    int src, dest, weight;
};

struct UnionFind
{
    int *parents;
    int count;
};

struct Graph
{
    int V, E;
    struct Edge *edge;
};

struct UnionFind *createUnionFind(int n)
{
    struct UnionFind *uf = (struct UnionFind *)malloc(sizeof(struct UnionFind));
    uf->parents = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        uf->parents[i] = i;
    }
    uf->count = n;
    return uf;
}

void resetUnionFind(struct UnionFind *uf, int n)
{
    for (int i = 0; i < n; i++)
    {
        uf->parents[i] = i;
    }
    uf->count = n;
}

int find(struct UnionFind *uf, int i)
{
    int parent = uf->parents[i];
    if (parent == i)
    {
        return i;
    }
    else
    {
        int root = find(uf, parent);
        uf->parents[i] = root;
        return root;
    }
}

void unionSets(struct UnionFind *uf, int i, int j)
{
    int r1 = find(uf, i);
    int r2 = find(uf, j);
    if (r1 != r2)
    {
        uf->count--;
        uf->parents[r1] = r2;
    }
}

void freeUnionFind(struct UnionFind *uf)
{
    free(uf->parents);
    free(uf);
}

int compareEdges(const void *a, const void *b)
{
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

int buildMST(struct Graph *graph, struct UnionFind *uf, int budget)
{
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    int cost = 0;
    int edgeCount = 0;

    for (int i = 0; i < graph->E; i++)
    {
        struct Edge next_edge = graph->edge[i];

        if (find(uf, next_edge.src) != find(uf, next_edge.dest))
        {
            if (cost + next_edge.weight <= budget)
            {
                cost += next_edge.weight;
                unionSets(uf, next_edge.src, next_edge.dest);
                edgeCount++;
            }
        }
    }

    // If the MST is not connected (edgeCount is V-1 for a connected graph)
    if (edgeCount != graph->V - 1)
    {
        return -1; // Indicates that a valid MST within the budget is not possible
    }

    return cost;
}

int main()
{
    int V, E, budget;
    // printf("Enter the number of vertices (V), edges (E), and budget: ");
    scanf("%d %d %d", &V, &E, &budget);

    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge *)malloc(E * sizeof(struct Edge));

    // printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    struct UnionFind *uf = createUnionFind(V);

    int minCost = buildMST(graph, uf, budget);

    if (minCost == -1)
    {
        printf("A valid MST within the budget is not possible.\n");
    }
    else
    {
        printf("Minimum Cost Spanning Tree within the budget: %d\n", minCost);
    }

    free(graph->edge);
    free(graph);
    freeUnionFind(uf);

    return 0;
}
