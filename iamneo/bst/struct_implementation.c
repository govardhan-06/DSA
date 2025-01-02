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

// Find nth maximum element using reverse inorder traversal
struct Node *n_find_max(int k, struct Node *T, int *count)
{
    if (T == NULL)
    {
        return NULL;
    }

    // First, go to the right subtree (largest elements)
    struct Node *right = n_find_max(k, T->right, count);
    if (right != NULL)
    {
        return right; // If found in right subtree, return it
    }

    // Visit the current node
    (*count)++;
    if (*count == k)
    {
        return T; // This is the nth largest element
    }

    // Now, go to the left subtree
    return n_find_max(k, T->left, count);
}

// Find nth minimum (smallest) element using inorder traversal
struct Node *n_find_min(int k, struct Node *T, int *count)
{
    if (T == NULL)
    {
        return NULL;
    }

    // First, go to the left subtree (smallest elements)
    struct Node *left = n_find_min(k, T->left, count);
    if (left != NULL)
    {
        return left; // If found in left subtree, return it
    }

    // Visit the current node
    (*count)++;
    if (*count == k)
    {
        return T; // This is the nth smallest element
    }

    // Now, go to the right subtree
    return n_find_min(k, T->right, count);
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

    // Inserting nodes into the BST
    root = insert(50, root);
    root = insert(30, root);
    root = insert(20, root);
    root = insert(40, root);
    root = insert(70, root);
    root = insert(60, root);
    root = insert(80, root);

    // Inorder traversal of the BST
    printf("Inorder traversal of the binary search tree:\n");
    inorder(root);
    printf("\n");

    // Deleting some nodes
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

    // Finding the nth maximum and minimum elements
    int count = 0;
    int k = 3; // Example: find 3rd largest and 3rd smallest
    struct Node *nth_largest = n_find_max(k, root, &count);
    if (nth_largest != NULL)
    {
        printf("The %dth largest element is: %d\n", k, nth_largest->data);
    }
    else
    {
        printf("Less than %d elements in the tree for kth largest.\n", k);
    }

    count = 0; // Reset count for the next search
    struct Node *nth_smallest = n_find_min(k, root, &count);
    if (nth_smallest != NULL)
    {
        printf("The %dth smallest element is: %d\n", k, nth_smallest->data);
    }
    else
    {
        printf("Less than %d elements in the tree for kth smallest.\n", k);
    }

    // Freeing allocated memory (optional)
    // You may implement a function to delete the entire tree if needed

    return 0;
}