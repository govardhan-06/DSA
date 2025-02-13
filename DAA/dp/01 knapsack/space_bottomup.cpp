#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// 0/1 Knapsack Problem
// Bottom-up Approach
// Space Optimized
// Time Complexity: O(n*maxWeight)
// Space Complexity: O(maxWeight)

int knapsack(int n, int maxWeight, vector<int> &wt, vector<int> &val)
{
    vector<int> prev(maxWeight + 1, 0), curr(maxWeight + 1, 0);
    for (int w = wt[0]; w <= maxWeight; w++)
        prev[w] = val[0];
    for (int ind = 1; ind < n; ind++)
    {
        for (int w = 1; w <= maxWeight; w++)
        {
            if (wt[ind] <= w)
                curr[w] = max(val[ind] + prev[w - wt[ind]], 0 + prev[w]);
            else
                curr[w] = prev[w];
        }
        prev = curr;
    }
    return prev[maxWeight];
}

int main()
{
    vector<int> wt = {10, 20, 30};
    vector<int> val = {60, 100, 120};
    int maxWeight = 50;
    cout << knapsack(wt.size(), maxWeight, wt, val) << endl;
    return 0;
}