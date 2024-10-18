#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *insert(int data, struct Node *T)
{
    if (T == NULL)
    {
        T = (struct Node *)malloc(sizeof(struct Node));
        if (T == NULL)
        {
            printf("No memory");
        }
        else
        {
            T->data = data;
            T->left = T->right = NULL;
        }
    }
    else
    {
        if (data < T->data)
        {
            T->left = insert(data, T->left);
        }
        else if (data > T->data)
        {
            T->right = insert(data, T->right);
        }
    }
    return T;
}

struct Node *find(int data, struct Node *T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else
    {
        if (data < T->data)
        {
            return find(data, T->left);
        }
        else if (data > T->data)
        {
            return find(data, T->right);
        }
        else
        {
            return T;
        }
    }
}

struct Node *find_min(struct Node *T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else
    {
        if (T->left == NULL)
        {
            return T;
        }
        else
        {
            return find_min(T->left);
        }
    }
}

struct Node *find_max(struct Node *T)
{
    if (T == NULL)
    {
        return NULL;
    }
    else
    {
        if (T->right == NULL)
        {
            return T;
        }
        else
        {
            return find_max(T->right);
        }
    }
}

struct Node *delete(int data, struct Node *T)
{
    struct Node *temp;
    if (T == NULL)
    {
        printf("No element found\n");
    }
    else
    {
        if (data < T->data)
        {
            T->left = delete (data, T->left);
        }
        else if (data > T->data)
        {
            T->right = delete (data, T->right);
        }
        else
        {
            if (T->left && T->right)
            {
                temp = find_min(T->right);
                T->data = temp->data;
                T->right = delete (T->data, T->right);
            }
            else
            {
                temp = T;
                if (T->left == NULL)
                {
                    T = T->right;
                }
                else if (T->right == NULL)
                {
                    T = T->left;
                }
                free(temp);
            }
        }
    }
    return T;
}

void inorder(struct Node *T)
{
    if (T != NULL)
    {
        inorder(T->left);
        printf("%d ", T->data); // Added space for better readability
        inorder(T->right);
    }
}

int main()
{
    struct Node *root = NULL;

    // Example operations
    root = insert(50, root);
    root = insert(30, root);
    root = insert(20, root);
    root = insert(40, root);
    root = insert(70, root);
    root = insert(60, root);
    root = insert(80, root);

    printf("Inorder traversal of the binary search tree:\n");
    inorder(root);
    printf("\n");

    root = delete (20, root);
    printf("Inorder traversal after deleting 20:\n");
    inorder(root);
    printf("\n");

    root = delete (30, root);
    printf("Inorder traversal after deleting 30:\n");
    inorder(root);
    printf("\n");

    root = delete (50, root);
    printf("Inorder traversal after deleting 50:\n");
    inorder(root);
    printf("\n");

    return 0;
}
