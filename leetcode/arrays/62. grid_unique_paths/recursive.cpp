#include <bits/stdc++.h>
using namespace std;

// Time complexity: O(2^(m+n))
// Space complexity: O(m+n)

class Solution
{
public:
    int countPaths(int i, int j, int m, int n)
    {
        if (i == m - 1 && j == n - 1)
            return 1;
        else if (i >= m || j >= n)
            return 0;
        return countPaths(i + 1, j, m, n, dp) + countPaths(i, j + 1, m, n, dp);
    }
    int uniquePaths(int m, int n)
    {
        return countPaths(0, 0, m, n);
    }
};