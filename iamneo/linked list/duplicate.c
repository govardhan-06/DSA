#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *nextNode;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->nextNode = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
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
    { // Fix to ensure we traverse to the last node
        curr = curr->nextNode;
    }
    curr->nextNode = newNode;
}

// Function to delete the last node
void deleteEnd(struct Node **head)
{
    if (*head == NULL)
    {
        printf("Empty List\n");
        return;
    }
    struct Node *temp = *head;
    if (temp->nextNode == NULL)
    { // If there's only one node
        free(temp);
        *head = NULL;
        return;
    }
    while (temp->nextNode->nextNode != NULL)
    { // Fix loop to find the second last node
        temp = temp->nextNode;
    }
    free(temp->nextNode);  // Free the last node
    temp->nextNode = NULL; // Set the new last node's nextNode to NULL
}

// Function to count occurrences of a given data
int count(struct Node **head, int data)
{
    if (*head == NULL)
    {
        printf("Empty List\n");
        return 0;
    }
    struct Node *temp = *head;
    int c = 0;
    while (temp != NULL)
    {
        if (temp->data == data)
        {
            c++;
        }
        temp = temp->nextNode;
    }
    return c;
}

// Function to remove duplicates from the linked list
void removeDuplicates(struct Node **head)
{
    if (*head == NULL)
    {
        printf("Empty List\n");
        return;
    }
    struct Node *current = *head, *prev = NULL;
    while (current != NULL)
    {
        if (count(head, current->data) > 1)
        {
            // Duplicate found, remove it
            struct Node *temp = current;
            if (prev == NULL)
            { // Handle case for head node
                *head = current->nextNode;
            }
            else
            {
                prev->nextNode = current->nextNode;
            }
            current = current->nextNode;
            free(temp);
        }
        else
        {
            prev = current;
            current = current->nextNode;
        }
    }
}

// Function to display the linked list
void display(struct Node *head)
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->nextNode;
    }
    printf("\n");
}

// Main function to test the implementation
int main()
{
    int T;
    scanf("%d", &T); // Number of test cases
    while (T--)
    {
        int n;
        scanf("%d", &n); // Number of elements in the linked list
        struct Node *head = NULL;

        for (int i = 0; i < n; i++)
        {
            int c;
            scanf("%d", &c);  // Read the data
            insert(&head, c); // Insert the data into the linked list
        }

        removeDuplicates(&head); // Remove duplicates
        display(head);           // Display the modified linked list
    }
    return 0;
}
