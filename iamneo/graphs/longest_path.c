#include <stdio.h>

#define MAX 5

// Directions arrays for 8 directions (N, S, E, W, NE, NW, SE, SW)
int rowDir[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int colDir[] = {0, 0, 1, -1, -1, 1, -1, 1};

// Matrix and visited array
char matrix[MAX][MAX];
int visited[MAX][MAX];

// Function to perform DFS
int dfs(int x, int y, char startChar, int n, int m)
{
    // Base case: if out of bounds or the character does not match the expected character
    if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || matrix[x][y] != startChar)
    {
        return 0;
    }

    // Mark current cell as visited
    visited[x][y] = 1;

    int maxLength = 1; // The current cell counts as a path of length 1

    // Explore all 8 directions
    for (int i = 0; i < 8; i++)
    {
        int newX = x + rowDir[i];
        int newY = y + colDir[i];

        // Call DFS for the next character which should be the next consecutive character
        if (newX >= 0 && newX < n && newY >= 0 && newY < m)
        {
            // Recursively call DFS for the next character
            int newLength = 1 + dfs(newX, newY, startChar + 1, n, m);
            maxLength = (maxLength > newLength) ? maxLength : newLength;
        }
    }

    // Unmark the current cell for other DFS calls
    visited[x][y] = 0;

    return maxLength;
}

int main()
{
    int n, m;

    // Input for matrix size
    scanf("%d", &n);
    scanf("%d", &m);

    // Input the matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf(" %c", &matrix[i][j]);
        }
    }

    // Character to start the longest path from
    char startChar;
    scanf(" %c", &startChar);

    // Initialize visited matrix to false
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = 0;
        }
    }

    // Find all starting positions of the character and perform DFS
    int longestPath = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] == startChar)
            {

                int pathLength = dfs(i, j, startChar, n, m);
                longestPath = (longestPath > pathLength) ? longestPath : pathLength;
            }
        }
    }

    printf("The length of the longest path with consecutive characters starting from character %c is %d\n", startChar, longestPath);

    return 0;
}
