#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Minimum number of multiplications required to multiply matrices
// Recursive approach with memoization
// Time complexity: O(n^3)
// Space complexity: O(n^2)
// Input: {40, 20, 30, 10, 30} -> 4 matrices with dimensions 40x20, 20x30, 30x10, 10x30

int LookupChain(vector<vector<int>> &m, vector<int> &p, int i, int j)
{
    if (m[i][j] != -1)
        return m[i][j];
    else if (i == j)
        return 0;
    int minCost = INT_MAX;
    for (int k = i; k < j; k++)
    {
        int q = LookupChain(m, p, i, k) + LookupChain(m, p, k + 1, j) + p[i - 1] * p[k] * p[j];
        minCost = min(q, minCost);
    }
    m[i][j] = minCost;
    return m[i][j];
}

int MatrixChainMultiplication(vector<int> &p)
{
    int n = p.size() - 1;
    vector<vector<int>> m(n, vector<int>(n, -1));
    return LookupChain(m, p, 1, n);
}

int main()
{
    vector<int> p = {40, 20, 30, 10, 30}; // Example matrix dimensions
    int minMultiplications = MatrixChainMultiplication(p);

    cout << "Minimum number of multiplications: " << minMultiplications << endl;
    return 0;
}