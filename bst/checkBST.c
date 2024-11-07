#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
struct Node *insert(struct Node *root)
{
    int leftdata, rightdata;
    if (root == NULL)
        return NULL;
    scanf("%d", &leftdata);
    if (leftdata != -1)
    {
        root->left = createNode(leftdata);
        insert(root->left);
    }
    scanf("%d", &rightdata);
    if (rightdata != -1)
    {
        root->right = createNode(rightdata);
        insert(root->right);
    }
    return root;
}

int checkBST(struct Node *root, int min, int max)
{
    if (root == NULL)
        return 1;
    if (root->data < min || root->data > max)
    {
        return 0;
    }
    return checkBST(root->left, min, root->data) && checkBST(root->right, root->data, max);
}

int isBST(struct Node *root)
{
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

int main()
{
    struct Node *root = NULL;
}