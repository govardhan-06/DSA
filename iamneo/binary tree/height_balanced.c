#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

struct Node *insertNode(struct Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else
    {
        root->right = insertNode(root->right, data);
    }
    return root;
}

int height(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight)
        return (leftHeight + 1);
    else
        return (rightHeight + 1);
}

bool isBalanced(struct Node *root)
{
    if (root == NULL)
        return true;

    int leftTree = height(root->left);
    int rightTree = height(root->right);

    if (abs(leftTree - rightTree) > 1)
        return false;

    return isBalanced(root->left) && isBalanced(root->right);
}

int main()
{
    int n;
    scanf("%d", &n);
    struct Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        int data;
        scanf("%d", &data);
        root = insertNode(root, data);
    }
    if (isBalanced(root))
        printf("The binary tree is height-balanced\n");
    else
        printf("The binary tree is not height-balanced\n");
}
