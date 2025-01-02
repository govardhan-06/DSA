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

struct Node *insert(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

struct Node *findLCA(struct Node *root, int n1, int n2)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data > n1 && root->data > n2)
    {
        return findLCA(root->left, n1, n2);
    }
    if (root->data < n1 && root->data < n2)
    {
        return findLCA(root->right, n1, n2);
    }
    return root;
}

int findDistance(struct Node *root, int value)
{
    if (root == NULL)
        return -1;
    if (root->data == value)
        return 0;

    int dist;
    if (value < root->data)
        dist = findDistance(root->left, value);
    else
        dist = findDistance(root->right, value);

    if (dist >= 0)
        return dist + 1;
    return -1;
}

int distanceBetweenNodes(struct Node *root, int n1, int n2)
{
    struct Node *lca = findLCA(root, n1, n2);
    int d1 = findDistance(lca, n1);
    int d2 = findDistance(lca, n2);
    return d1 + d2;
}

int main()
{
    struct Node *root = NULL;
    int n, data;

    // Input the number of nodes
    scanf("%d", &n);

    // Insert nodes into the BST
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        root = insert(root, data);
    }

    int n1, n2;
    scanf("%d %d", &n1, &n2);
    int distance = distanceBetweenNodes(root, n1, n2);
    printf("Distance: %d\n", distance);

    return 0;
}
