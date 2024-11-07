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

    // Since the graph is undirected, add the reverse edge as well.
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void BFS(struct Graph *graph, int startvertex)
{
    int *queue = (int *)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;
    graph->visited[startvertex] = 1;
    queue[rear++] = startvertex;

    while (front != rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        struct Node *temp = graph->adjList[currentVertex];

        struct Node *prev = NULL, *next = NULL;
        while (temp)
        {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }

        temp = prev;
        while (temp)
        {
            int adjVertex = temp->data;
            if (graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    free(queue);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m); // Read number of vertices and edges

    struct Graph *graph = createGraph(n);

    // Read the edges and add them to the graph
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int startVertex;
    scanf("%d", &startVertex); // Read the starting vertex for BFS

    // Perform BFS
    BFS(graph, startVertex);

    return 0;
}
