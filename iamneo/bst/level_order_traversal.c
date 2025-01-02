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

// Function to insert a new node in the BST
struct Node *insert(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    // Duplicate values are ignored
    return root;
}

// Function to perform level order traversal
void levelOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    struct Node **queue = (struct Node **)malloc(100 * sizeof(struct Node *)); // Allocate queue for level order traversal
    int front = 0, rear = 0;

    queue[rear++] = root; // Start with the root node

    while (front < rear)
    {
        struct Node *current = queue[front++]; // Get the current node from the queue
        printf("%d ", current->data);          // Print the current node's data

        // Enqueue left child
        if (current->left != NULL)
            queue[rear++] = current->left;

        // Enqueue right child
        if (current->right != NULL)
            queue[rear++] = current->right;
    }

    free(queue); // Free the allocated memory for the queue
}

int main()
{
    struct Node *root = NULL;
    int data;

    // Read input until a non-positive integer is encountered
    while (1)
    {
        scanf("%d", &data);
        if (data <= 0)
            break;
        root = insert(root, data);
    }

    // Perform level order traversal
    levelOrderTraversal(root);
    printf("\n"); // Print a newline at the end

    return 0;
}
