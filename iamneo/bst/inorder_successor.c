#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
struct Node *insert(struct Node *root, int data)
{
    if (root == NULL)
        return createNode(data);
    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) // Corrected this line
    {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to perform in-order traversal and store values in the array
void inorder(struct Node *root, int *arr, int *index)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left, arr, index);  // Visit left subtree
    arr[(*index)++] = root->data;     // Store current node's data
    inorder(root->right, arr, index); // Visit right subtree
}

int main()
{
    struct Node *root = NULL;
    int data = 0;

    printf("Enter nodes for BST (non-positive integer to stop):\n");
    while (1)
    {
        scanf("%d", &data);
        if (data <= 0)
        {
            break;
        }
        root = insert(root, data); // Corrected: assign the result of insert
    }

    int search = 0;
    printf("Enter the value to find its in-order successor:\n");
    scanf("%d", &search);

    // Prepare array and index for in-order traversal
    int arr[100];
    int index = 0;
    inorder(root, arr, &index); // Pass index by reference

    // Find and print in-order successor
    for (int i = 0; i < index - 1; i++) // Only iterate to index - 1
    {
        if (arr[i] == search)
        {
            printf("In-order Successor of %d is %d\n", search, arr[i + 1]);
            return 0; // Exit after finding the successor
        }
    }

    printf("In-order Successor doesn't exist\n"); // If successor not found
    return 0;
}
