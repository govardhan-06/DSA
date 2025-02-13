#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// 0/1 Knapsack Problem
// Recursive Approach without memoization
// Time Complexity: O(2^n)
// Space Complexity: O(1)

int f(int ind, int maxWeight, vector<int> &wt, vector<int> &val)
{
    if (ind == 0)
    {
        if (wt[ind] <= maxWeight)
            return val[ind];
        return 0;
    }
    int not_take = 0 + f(ind - 1, maxWeight, wt, val);
    int take = INT_MIN;
    if (wt[ind] <= maxWeight)
        take = val[ind] + f(ind - 1, maxWeight - wt[ind], wt, val);
    return max(take, not_take);
}

int main()
{
    vector<int> wt = {10, 20, 30};
    vector<int> val = {60, 100, 120};
    int maxWeight = 50;
    cout << f(wt.size() - 1, maxWeight, wt, val) << endl;
    return 0;
}