#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    long f(int ind, int buy, vector<int> &prices, int n, vector<vector<long>> &dp)
    {
        if (ind == n)
            return 0; // Base case
        if (dp[ind][buy] != -1)
            return dp[ind][buy]; // Return cached result

        long profit = 0;
        if (buy)
        {
            profit = max(-prices[ind] + f(ind + 1, 0, prices, n, dp),
                         0 + f(ind + 1, 1, prices, n, dp));
        }
        else
        {
            profit = max(prices[ind] + f(ind + 1, 1, prices, n, dp),
                         0 + f(ind + 1, 0, prices, n, dp));
        }
        return dp[ind][buy] = profit; // Store result in dp array
    }

    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<long>> dp(n, vector<long>(2, -1)); // Memoization table
        return f(0, 1, prices, n, dp);
    }
};
