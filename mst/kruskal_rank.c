#include <stdio.h>
#include <stdlib.h>

struct Edge
{
    int src;
    int dest;
    int weight;
};

struct UnionFind
{
    int *parents;
    int *rank;
};

struct UnionFind *createUnionFind(int n)
{
    struct UnionFind *uf = (struct UnionFind *)malloc(sizeof(struct UnionFind));
    uf->parents = (int *)malloc(n * sizeof(int));
    uf->rank = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        uf->parents[i] = i;
        uf->rank[i] = 0;
    }
    return uf;
}

int find(struct UnionFind *uf, int i)
{
    if (uf->parents[i] == i)
        return i;
    else
    {
        int root = find(uf, uf->parents[i]);
        uf->parents[i] = root;
        return root;
    }
}

void unionSets(struct UnionFind *uf, int i, int j)
{
    // rank approach
    int r1 = find(uf, i);
    int r2 = find(uf, j);
    if (r1 != r2)
    {
        if (uf->rank[r1] < uf->rank[r2])
            uf->parents[r1] = r2;
        else if (uf->rank[r1] > uf->rank[r2])
            uf->parents[r2] = r1;
        else
        {
            uf->parents[r2] = r1;
            uf->rank[r1]++;
        }
    }
}

int compareEdges(const void *a, const void *b)
{
    return (((struct Edge *)a)->weight - (((struct Edge *)b)->weight));
}

int buildMST(int V, struct Edge *edges, int E)
{
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    int cost = 0;
    int edgeCount = 0;
    struct UnionFind *uf = createUnionFind(V);
    for (int i = 0; i < E; i++)
    {
        int source = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        if (find(uf, source) != find(uf, dest))
        {
            unionSets(uf, source, dest);
            cost += weight;
            edgeCount++;
            if (edgeCount == V - 1)
                break;
        }
    }
    if (edgeCount < V - 1)
        return -1;
    return cost;
}

int main()
{
    int V, E;
    scanf("%d", &V);
    scanf("%d", &E);
    struct Edge *edges = (struct Edge *)malloc(sizeof(struct Edge));
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }
    int mincost = buildMST(V, edges, E);
    if (mincost == -1)
        printf("Not possible");
    else
        printf("Valid MST; cost: %d", mincost);

    free(edges);
}