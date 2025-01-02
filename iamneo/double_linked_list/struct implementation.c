#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prevNode;
    struct Node *nextNode;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

void insert(struct Node **head, int data)
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
    newNode->nextNode = NULL;
}

void display(struct Node **head)
{
    struct Node *temp = *head;
    if (*head == NULL)
    {
        printf("List is empty");
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
        insert(&head, c);
    }
    display(&head);
}
