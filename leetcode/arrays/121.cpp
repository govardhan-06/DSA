#include <iostream>
#include <vector>
using namespace std;

// stock buy and sell
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int max_profit = 0;
        int min_stock = INT_MAX;
        for (int i = 0; i < prices.size(); i++)
        {
            min_stock = min(min_stock, prices[i]);
            max_profit = max(max_profit, prices[i] - min_stock);
        }
        return max_profit;
    }
};