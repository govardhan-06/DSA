#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node *buildTree(struct Node *root, int arr[], int i, int n)
{
    if (i < n)
    {
        struct Node *temp = createNode(arr[i]);
        root = temp;
        root->left = buildTree(root->left, arr, 2 * i + 1, n);
        root->right = buildTree(root->right, arr, 2 * i + 2, n);
    }
    return root;
}

void levelOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        printf("EMPTY TREE\n");
        return;
    }
    struct Node **queue = (struct Node **)malloc(100 * sizeof(struct Node *));
    int front = -1, rear = -1;
    struct Node **stack = (struct Node **)malloc(100 * sizeof(struct Node *));
    int top = -1;
    queue[++rear] = root;
    while (front < rear)
    {
        struct Node *current = queue[++front];
        stack[++top] = current;
        if (current->left != NULL)
            queue[++rear] = current->left;
        if (current->right != NULL)
            queue[++rear] = current->right;
    }
    for (int i = 0; i < top + 1; i++)
    {
        printf("%d ", stack[i]->data);
    }
    printf("\n");
    free(queue);
    free(stack);
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    struct Node *root = NULL;
    root = buildTree(root, arr, 0, n);
    levelOrderTraversal(root);
}