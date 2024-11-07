#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

struct Node *build()
{
    int data = 0;
    scanf("%d", &data);
    if (data == -1)
        return NULL;
    struct Node *root = createNode(data);
    root->left = build();
    root->right = build();
    return root;
}

int maxVal(struct Node *root, int *maxSum)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftSum = maxVal(root->left, maxSum);
    int rightSum = maxVal(root->right, maxSum);
    leftSum = (leftSum > 0) ? leftSum : 0;
    rightSum = (rightSum > 0) ? rightSum : 0;
    int currSum = root->data + leftSum + rightSum;
    *maxSum = (*maxSum > currSum) ? *maxSum : currSum;
    return root->data + (leftSum > rightSum ? leftSum : rightSum);
}

int maxPathSum(struct Node *root)
{
    int maxSum = INT_MIN;
    maxVal(root, &maxSum);
    return maxSum;
}

int main()
{
    struct Node *root = build();
    int result = maxPathSum(root);
    printf("%d", result);
}