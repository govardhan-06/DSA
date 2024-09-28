#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *nextNode;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->nextNode = NULL;
    return newNode;
}

void insertatBeginning(struct Node **headref, int data)
{
    struct Node *newNode = createNode(data);
    newNode->nextNode = *headref;
    *headref = newNode;
}

void appendatEnd(struct Node **headref, int data)
{
    struct Node *newNode = createNode(data);
    if (*headref == NULL)
    {
        *headref = newNode;
        return;
    }
    struct Node *temp = *headref;
    // Correct the condition here
    while (temp->nextNode != NULL)
    {
        temp = temp->nextNode;
    }
    temp->nextNode = newNode;
}

void insertatMiddle(struct Node **headref, int data, int pos)
{
    struct Node *newNode = createNode(data);
    if (pos == 1)
    {
        newNode->nextNode = *headref;
        *headref = newNode;
        return;
    }
    struct Node *temp = *headref;
    for (int i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->nextNode;
    }
    if (temp == NULL)
    {
        printf("Out of bounds\n");
        free(newNode);
        return;
    }

    newNode->nextNode = temp->nextNode;
    temp->nextNode = newNode;
}

void print(struct Node *headref)
{
    struct Node *temp = headref;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->nextNode;
    }
    printf("NULL\n");
}

void deleteNode(struct Node **headref, int pos)
{
    if (*headref == NULL)
    {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = *headref;
    if (pos == 1)
    {
        *headref = temp->nextNode;
        free(temp);
        return;
    }
    struct Node *prev = NULL;
    for (int i = 1; i < pos && temp != NULL; i++)
    {
        prev = temp;
        temp = temp->nextNode;
    }
    if (temp == NULL)
    {
        printf("Position out of bounds\n");
        return;
    }
    prev->nextNode = temp->nextNode;
    free(temp);
}

int main()
{
    struct Node *head = NULL;

    // Inserting elements at the beginning
    insertatBeginning(&head, 10);
    insertatBeginning(&head, 20);

    // Appending elements at the end
    appendatEnd(&head, 30);
    appendatEnd(&head, 40);

    // Inserting element in the middle at position 3
    insertatMiddle(&head, 25, 3);

    // Printing the list
    printf("Linked list after insertions: ");
    print(head);

    // Deleting node at position 3
    deleteNode(&head, 3);

    // Printing the list after deletion
    printf("Linked list after deletion: ");
    print(head);

    return 0;
}
