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
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    newNode->data = data;
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
    newNode->nextNode = *head;
    (*head)->prevNode = newNode;
    *head = newNode;
}

int count(struct Node **head, int data)
{
    struct Node *temp = *head;
    int count = 0;
    while (temp != NULL)
    {
        if (temp->data == data)
        {
            count++;
        }
        temp = temp->nextNode;
    }
    return count;
}

void sort(struct Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty");
        return;
    }
    struct Node *temp = *head;
    while (temp != NULL)
    {
        if (count(head, temp->data) > 1)
        {
            struct Node *nodeDel = temp;
            struct Node *nextNode = temp->nextNode;
            if (nodeDel->prevNode == NULL)
            {
                *head = nextNode;
                if (*head != NULL)
                {
                    (*head)->prevNode = NULL;
                }
            }
            else
            {
                nodeDel->prevNode->nextNode = nextNode;
                if (nodeDel->nextNode != NULL)
                {
                    nodeDel->nextNode->prevNode = nodeDel->prevNode;
                }
            }
            free(nodeDel);
            temp = nextNode;
        }
        else
        {
            temp = temp->nextNode;
        }
    }
}

void display(struct Node **head)
{
    struct Node *temp = *head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->nextNode;
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    struct Node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        scanf("%d", &c);
        insert(&head, c);
    }
    sort(&head);
    display(&head);
}
