#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Longest Common Subsequence
// Recursion with Memoization
// Time Complexity: O(n*m)
// Space Complexity: O(n*m) + O(n*m){auxillary stack space} = O(n*m)

int findLCS(int i, int j, string s, string t, vector<vector<int>> &dp)
{
    int n = s.size(), m = t.size();
    if (i < 0 || j < 0)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    if (s[i] == t[j])
        return dp[i][j] = 1 + findLCS(i - 1, j - 1, s, t, dp);
    return dp[i][j] = max(findLCS(i - 1, j, s, t, dp), findLCS(i, j - 1, s, t, dp));
}

int main()
{
    string s = "acd";
    string t = "ced";
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    cout << findLCS(n - 1, m - 1, s, t, dp);
}