#include <stdlib.h>
#include <stdio.h>

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

struct Node *insertNode(int arr[], int index, int n)
{
    struct Node *root = NULL;
    if (index < n)
    {
        root = createNode(arr[index]);
        root->left = insertNode(arr, 2 * index + 1, n);
        root->right = insertNode(arr, 2 * index + 2, n);
    }
    return root;
}

void inorder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    if (root->data % 2 != 0)
    {
        printf("%d", root->data);
    }
    inorder(root->right);
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
    int i = 0;
    struct Node *root = insertNode(arr, i, n);
    inorder(root);
}