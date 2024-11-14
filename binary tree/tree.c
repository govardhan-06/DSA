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

struct Node *createTree(int arr[], struct Node *root, int index, int n)
{
    if (index < n)
    {
        struct Node *temp = createNode(arr[index]);
        root = temp;
        root->left = createTree(arr, root->left, 2 * index + 1, n);
        root->right = createTree(arr, root->right, 2 * index + 2, n);
    }
    return root;
}

void preorder(struct Node *root, int threshold)
{
    if (root == NULL)
    {
        return;
    }
    if (root->data < threshold)
        printf("%d ", root->data);
    preorder(root->left, threshold);
    preorder(root->right, threshold);
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
    int thres;
    scanf("%d", &thres);
    int i = 0;
    struct Node *root = NULL;
    root = createTree(arr, root, i, n);
    preorder(root, thres);
}
