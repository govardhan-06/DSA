#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Longest Geometric Progression Sequence
// Time Complexity: O(n^2)
// Space Complexity: O(n^2)

// intialising a unordered map of double and int
// unordered_map<double, int> dp[n + 1];
// or this way for VPROPEL: vector<unordered_map<double, int> dp(n + 1);

int longestGP(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 2)
        return n;
    int ans = 0;
    vector<unordered_map<double, int>> dp(n + 1);
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] == 0)
                continue;
            double r = (double)arr[i] / arr[j];
            int count = 1;
            if (dp[j].find(r) != dp[j].end())
            {
                count = dp[j][r];
            }
            dp[i][r] = 1 + count;
            ans = max(ans, dp[i][r]);
        }
    }
    return ans;
}

int main()
{
    vector<int> arr = {6, 100, 18, 54};
    cout << longestGP(arr) << endl;
    return 0;
}