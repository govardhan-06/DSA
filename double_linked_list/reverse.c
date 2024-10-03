#include <stdio.h>
#include <stdlib.h>

// Define the structure for a doubly linked list node
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Function to reverse the doubly linked list
void reverseDoublyLinkedList(struct Node **head)
{
    struct Node *temp = NULL;
    struct Node *current = *head;

    // Swap next and prev for each node
    while (current != NULL)
    {
        temp = current->prev;          // Store the previous node
        current->prev = current->next; // Swap prev and next
        current->next = temp;          // Move to the next node
        current = current->prev;       // Move to the next node (previously next)
    }

    // Update head pointer to the new front
    if (temp != NULL)
    {
        *head = temp->prev; // Update head to the last processed node
    }
}

// Function to print the doubly linked list
void printList(struct Node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Main function to demonstrate the reversal of a doubly linked list
int main()
{
    struct Node *head = NULL;

    // Insert elements into the doubly linked list
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);
    insertEnd(&head, 40);
    insertEnd(&head, 50);

    printf("Original Doubly Linked List: ");
    printList(head);

    // Reverse the doubly linked list
    reverseDoublyLinkedList(&head);

    printf("Reversed Doubly Linked List: ");
    printList(head);

    return 0;
}
