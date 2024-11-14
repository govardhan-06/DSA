#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int key)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node *createBinaryTree(int numNodes)
{
    struct Node *root = NULL;
    int i, nodeValue;

    for (i = 0; i < numNodes; i++)
    {
        scanf("%d", &nodeValue);
        if (root == NULL)
            root = newNode(nodeValue);
        else
        {
            struct Node *temp = root;
            while (temp->left != NULL && temp->right != NULL)
            {
                temp = temp->left;
            }
            if (temp->left == NULL)
                temp->left = newNode(nodeValue);
            else
                temp->right = newNode(nodeValue);
        }
    }
    return root;
}

int height(struct Node *node)
{
    if (node == NULL)
        return 0;
    else
    {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

int printLevel(struct Node *root, int level)
{
    if (root == NULL)
        return 0;

    if (level == 1)
    {
        printf("%d ", root->key);
        return 1;
    }

    int left = printLevel(root->left, level - 1);
    int right = printLevel(root->right, level - 1);

    return left || right;
}

void levelOrderTraversal(struct Node *root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printLevel(root, i);
}

int main()
{
    int numNodes;
    struct Node *root = NULL;

    scanf("%d", &numNodes);

    root = createBinaryTree(numNodes);

    levelOrderTraversal(root);

    return 0;
}