#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// 0/1 Knapsack Problem
// Bottom-up Approach
// Time Complexity: O(n*maxWeight)
// Space Complexity: O(n*maxWeight)

int knapsack(int n, int maxWeight, vector<int> &wt, vector<int> &val)
{
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));
    for (int w = wt[0]; w <= maxWeight; w++)
        dp[0][w] = val[0];
    for (int ind = 1; ind < n; ind++)
    {
        for (int w = 1; w <= maxWeight; w++)
        {
            if (wt[ind] <= w)
                dp[ind][w] = max(val[ind] + dp[ind - 1][w - wt[ind]], 0 + dp[ind - 1][w]);
            else
                dp[ind][w] = dp[ind - 1][w];
        }
    }
    return dp[n - 1][maxWeight];
}

int main()
{
    vector<int> wt = {10, 20, 30};
    vector<int> val = {60, 100, 120};
    int maxWeight = 50;
    cout << knapsack(wt.size(), maxWeight, wt, val) << endl;
    return 0;
}