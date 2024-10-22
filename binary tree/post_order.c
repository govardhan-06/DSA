#include <stdio.h>
#include <stdlib.h>

// Binary Tree Node structure
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Queue Node structure (for level-order traversal)
struct QueueNode
{
    struct Node *treeNode;
    struct QueueNode *next;
};

// Function to create a new tree node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a new queue node
struct QueueNode *createQueueNode(struct Node *treeNode)
{
    struct QueueNode *qNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    qNode->treeNode = treeNode;
    qNode->next = NULL;
    return qNode;
}

// Check if the queue is empty
int isQueueEmpty(struct QueueNode *front)
{
    return front == NULL;
}

// Function to enqueue a tree node into the queue
void enqueue(struct QueueNode **front, struct QueueNode **rear, struct Node *treeNode)
{
    struct QueueNode *temp = createQueueNode(treeNode);
    if (*rear == NULL)
    {
        // If the queue is empty, both front and rear should point to the new node
        *front = *rear = temp;
    }
    else
    {
        // Otherwise, add the new node at the end and update rear
        (*rear)->next = temp;
        *rear = temp;
    }
}

// Function to dequeue a node from the queue
struct Node *dequeue(struct QueueNode **front, struct QueueNode **rear)
{
    if (isQueueEmpty(*front))
    {
        return NULL;
    }
    struct QueueNode *temp = *front;
    *front = (*front)->next; // Move front to the next node

    // If front becomes NULL, also set rear to NULL
    if (*front == NULL)
    {
        *rear = NULL;
    }

    struct Node *treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

// Function to build a binary tree from an array using level order
struct Node *buildTree(int *arr, int n)
{
    if (n == 0)
        return NULL;

    struct Node *root = createNode(arr[0]);
    struct QueueNode *front = NULL, *rear = NULL;

    enqueue(&front, &rear, root);

    int i = 1;
    while (i < n)
    {
        struct Node *current = dequeue(&front, &rear); // Pass both front and rear
        if (i < n)
        {
            current->left = createNode(arr[i++]);
            enqueue(&front, &rear, current->left);
        }
        if (i < n)
        {
            current->right = createNode(arr[i++]);
            enqueue(&front, &rear, current->right);
        }
    }
    return root;
}

// Function to print the post order traversal of the binary tree
void postOrder(struct Node *root)
{
    if (root == NULL)
        return;
    else
    {
        if (root->left != NULL)
        {
            postOrder(root->left);
        }
        if (root->right != NULL)
        {
            postOrder(root->right);
        }
        printf("%d ", root->data);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    struct Node *root = buildTree(arr, n);
    postOrder(root);
    return 0;
}
