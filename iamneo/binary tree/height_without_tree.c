#include <stdio.h>
#define MAX_NODES 10

int findHeight(int parent[], int n)
{
    int depth[MAX_NODES] = {0}; // Array to store the depth of each node
    int maxHeight = 0;

    for (int i = 0; i < n; i++)
    {
        int height = 0;
        int currentNode = i;

        // Traverse up to the root node to calculate the depth of the current node
        while (parent[currentNode] != -1)
        {
            if (depth[currentNode] != 0)
            { // Use previously calculated depth if available
                height += depth[currentNode];
                break;
            }
            height++;
            currentNode = parent[currentNode];
        }

        depth[i] = height; // Store the calculated depth for node i

        if (height > maxHeight)
        { // Update the maximum height of the tree
            maxHeight = height;
        }
    }

    return maxHeight;
}

int main()
{
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int parent[MAX_NODES];

    printf("Enter the parent array:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &parent[i]);
    }

    int height = findHeight(parent, n);
    printf("The height of the binary tree is: %d\n", height);

    return 0;
}