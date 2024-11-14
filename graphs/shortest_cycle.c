#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

struct Edge
{
    int vertex;
    int weight;
};

int shortestCycleLength(struct Edge **graph, int vertices)
{
    int minCycleLength = INF;

    for (int start = 0; start < vertices; start++)
    {
        int *distance = (int *)malloc(vertices * sizeof(int));
        for (int i = 0; i < vertices; i++)
        {
            distance[i] = INF;
        }

        int *visited = (int *)malloc(vertices * sizeof(int));
        for (int i = 0; i < vertices; i++)
        {
            visited[i] = 0;
        }

        int *queue = (int *)malloc(vertices * sizeof(int));
        int front = 0, rear = 0;

        distance[start] = 0;
        visited[start] = 1;
        queue[rear++] = start;

        while (front != rear)
        {
            int curr = queue[front++];

            for (int i = 0; i < vertices; i++)
            {
                if (graph[curr][i].weight != INF)
                {
                    int neighbor = graph[curr][i].vertex;
                    int weight = graph[curr][i].weight;

                    if (!visited[neighbor])
                    {
                        visited[neighbor] = 1;
                        distance[neighbor] = distance[curr] + weight;
                        queue[rear++] = neighbor;
                    }
                    else if (neighbor == start)
                    {
                        minCycleLength = minCycleLength < distance[curr] + weight ? minCycleLength : distance[curr] + weight;
                    }
                }
            }
        }

        free(distance);
        free(visited);
        free(queue);
    }

    return minCycleLength;
}

int main()
{
    int vertices, edges;
    scanf("%d", &vertices);
    scanf("%d", &edges);

    struct Edge **graph = (struct Edge **)malloc(vertices * sizeof(struct Edge *));
    for (int i = 0; i < vertices; i++)
    {
        graph[i] = (struct Edge *)malloc(vertices * sizeof(struct Edge));
        for (int j = 0; j < vertices; j++)
        {
            graph[i][j].vertex = j;
            graph[i][j].weight = INF;
        }
    }

    for (int i = 0; i < edges; i++)
    {
        int source, destination, weight;
        scanf("%d %d %d", &source, &destination, &weight);
        graph[source][destination].weight = weight;
    }

    int shortestCycle = shortestCycleLength(graph, vertices);

    if (shortestCycle == INF)
    {
        printf("No cycle found in the graph.\n");
    }
    else
    {
        printf("Length of the shortest cycle: %d\n", shortestCycle);
    }

    // Free allocated memory
    for (int i = 0; i < vertices; i++)
    {
        free(graph[i]);
    }
    free(graph);

    return 0;
}