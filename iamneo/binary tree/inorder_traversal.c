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

struct Node *createTree(int totalNodes)
{
    struct Node *root = NULL;
    int data;
    for (int i = 0; i < totalNodes; i++)
    {
        scanf("%d", &data);
        if (root == NULL)
        {
            root = createNode(data);
        }
        else
        {
            struct Node *temp = root;
            while (temp->left != NULL && temp->right != NULL)
            {
                temp = temp->left;
            }
            if (temp->left == NULL)
                temp->left = createNode(data);
            else
                temp->right = createNode(data);
        }
    }
    return root;
}

void inorder(struct Node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main()
{
    int n;
    scanf("%d", &n);
    struct Node *root = createTree(n);
    inorder(root);
}