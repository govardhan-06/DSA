#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Graph
{
    int numVertices;
    struct Node **adjList;
    int *visited;
};

struct Graph *createGraph(int vertices)
{
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjList = (struct Node **)malloc(vertices * sizeof(struct Node *));
    graph->visited = (int *)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++)
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph *graph, int src, int dest)
{
    struct Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void DFS(struct Graph *graph, int vertex)
{
    struct Node *adjList = graph->adjList[vertex];
    struct Node *temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL)
    {
        int connectVertex = temp->data;
        if (graph->visited[connectVertex] == 0)
            DFS(graph, connectVertex);
        temp = temp->next;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    struct Graph *graph = createGraph(n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int startVertex;
    scanf("%d", &startVertex);

    DFS(graph, startVertex);

    return 0;
}