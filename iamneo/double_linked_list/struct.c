#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prevNode;
    struct Node *nextNode;
};

// Function prototypes
struct Node *createNode(int data);
void insertHead(struct Node **head, int data);
void insertEnd(struct Node **head, int data);
void insertPos(struct Node **head, int data, int pos);
void deleteNode(struct Node **head, int pos);
void displayList(struct Node *head);

int main()
{
    struct Node *head = NULL;

    // Insert nodes at the head
    insertHead(&head, 10);
    insertHead(&head, 5);

    // Insert nodes at the end
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    // Insert at a specific position
    insertPos(&head, 15, 3); // Insert 15 at position 3

    // Display the list after insertions
    printf("List after insertions: ");
    displayList(head);

    // Delete a node at position 1
    deleteNode(&head, 1);
    printf("List after deleting node at position 1: ");
    displayList(head);

    // Delete a node at position 3
    deleteNode(&head, 3);
    printf("List after deleting node at position 3: ");
    displayList(head);

    // Delete a node at position 4 (out of bounds case)
    deleteNode(&head, 4);
    printf("Attempted to delete node at position 4: ");
    displayList(head);

    return 0;
}

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

// Insert at the head of the list
void insertHead(struct Node **head, int data)
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

// Insert at the end of the list
void insertEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->nextNode != NULL)
    {
        temp = temp->nextNode;
    }
    temp->nextNode = newNode;
    newNode->prevNode = temp;
}

// Insert at a specific position in the list
void insertPos(struct Node **head, int data, int pos)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct Node *temp = *head;

    if (pos == 1)
    {
        newNode->nextNode = *head;
        (*head)->prevNode = newNode;
        *head = newNode;
        return;
    }

    // Traverse to the node before the insertion position
    for (int i = 1; i < pos - 1 && temp != NULL; i++)
    {
        temp = temp->nextNode;
    }

    // If the position is out of bounds
    if (temp == NULL || (temp->nextNode == NULL && pos != 2))
    {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }

    newNode->nextNode = temp->nextNode;
    if (temp->nextNode != NULL)
    {
        temp->nextNode->prevNode = newNode;
    }
    newNode->prevNode = temp;
    temp->nextNode = newNode;
}

// Delete a node at a specific position
void deleteNode(struct Node **head, int pos)
{
    if (*head == NULL)
    {
        printf("Empty list\n");
        return;
    }

    struct Node *curr = *head;

    if (pos == 1)
    {
        *head = curr->nextNode;
        if (*head != NULL)
        {
            (*head)->prevNode = NULL;
        }
        free(curr);
        return;
    }

    // Traverse to the node to be deleted
    for (int i = 1; curr != NULL && i < pos; i++)
    {
        curr = curr->nextNode;
    }

    // If position is out of bounds
    if (curr == NULL)
    {
        printf("Position out of bounds\n");
        return;
    }

    if (curr->prevNode != NULL)
    {
        curr->prevNode->nextNode = curr->nextNode;
    }

    if (curr->nextNode != NULL)
    {
        curr->nextNode->prevNode = curr->prevNode;
    }

    free(curr);
}

// Display the list
void displayList(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->nextNode;
    }
    printf("\n");
}
