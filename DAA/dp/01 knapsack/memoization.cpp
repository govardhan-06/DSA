#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// 0/1 Knapsack Problem
// Recursive Approach with memoization
// Time Complexity: O(n*maxWeight)
// Space Complexity: O(n*maxWeight)

int f(int ind, int maxWeight, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        if (wt[ind] <= maxWeight)
            return val[ind];
        return 0;
    }
    if (dp[ind][maxWeight] != -1)
        return dp[ind][maxWeight];
    int not_take = 0 + f(ind - 1, maxWeight, wt, val, dp);
    int take = INT_MIN;
    if (wt[ind] <= maxWeight)
        take = val[ind] + f(ind - 1, maxWeight - wt[ind], wt, val, dp);
    return dp[ind][maxWeight] = max(take, not_take);
}

int main()
{
    vector<int> wt = {10, 20, 30};
    vector<int> val = {60, 100, 120};
    int n = wt.size();
    int maxWeight = 50;
    vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
    cout << f(wt.size() - 1, maxWeight, wt, val, dp) << endl;
    return 0;
}