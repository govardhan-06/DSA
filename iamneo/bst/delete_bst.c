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
    if (data > root->data)
    {
        root->right = insertNode(root->right, data);
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
    printf("%d ", root->data);
    inorder(root->right);
}

struct Node *delete(struct Node *root, int avg)
{
    if (root == NULL)
    {
        return NULL;
    }
    delete (root->right, avg);
    if (root->data > avg)
    {
        struct Node *temp = root->left;
        free(root);
        return temp;
    }
    delete (root->left, avg);
    return root;
}

int main()
{
    int n;
    scanf("%d", &n);
    struct Node *root = NULL;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int d;
        scanf("%d", &d);
        sum += d;
        root = insertNode(root, d);
    }
    int avg = (int)(sum / n);
    printf("Before Deletion: ");
    inorder(root);
    printf("\n");
    root = delete (root, avg);
    printf("After Deletion: ");
    inorder(root);
}
