#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *nextNode;
    struct Node *prevNode;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

void enqueue(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *curr = *head;
    while (curr->nextNode != NULL)
    {
        curr = curr->nextNode;
    }
    curr->nextNode = newNode;
    newNode->prevNode = curr;
}

void dequeue(struct Node **head)
{
    if (*head == NULL)
    {
        printf("Queue is empty");
        return;
    }
    struct Node *nodeDel = *head;
    struct Node *nextNode = (*head)->nextNode;
    free(nodeDel);
    *head = nextNode;
    if (nextNode != NULL)
    {
        nextNode->prevNode = NULL;
    }
}

void display(struct Node **head)
{
    struct Node *temp = *head;
    if (*head == NULL)
    {
        printf("Queue is empty");
        return;
    }
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->nextNode;
    }
}

int main()
{
    int n = 0;
    struct Node *head = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        scanf("%d", &c);
        enqueue(&head, c);
    }
    dequeue(&head);
    display(&head);
}
