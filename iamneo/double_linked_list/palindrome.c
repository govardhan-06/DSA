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

void palindrome(struct Node **head)
{
    if ((*head)->next == NULL || *head == NULL)
    {
        printf("Palindrome");
        return;
    }
    struct Node *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    while (*head != tail && tail->next != *head)
    {
        if ((*head)->data != tail->data)
        {
            printf("Not a palindrome");
            return;
        }
        *head = (*head)->next;
        tail = tail->prev;
    }
    printf("Palindrome");
    return;
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
    insertEnd(&head, 30);
    insertEnd(&head, 10);

    printf("Original Doubly Linked List: ");
    printList(head);

    palindrome(&head);

    return 0;
}
