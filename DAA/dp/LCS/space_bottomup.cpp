#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Longest Common Subsequence
// Bottom Up Approach with space optimization
// Time Complexity: O(n*m)
// Space Complexity: O(m)

int findLCS(string &s, string &t)
{
    int n = s.size(), m = t.size();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);
    for (int j = 0; j <= m; j++)
        prev[j] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }
    return prev[m];
}

int main()
{
    string s = "acd", t = "ced";
    cout << findLCS(s, t);
}