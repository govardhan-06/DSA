#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Merge Overlapping intervals
class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> sol;
        for (int i = 0; i < n; i++)
        {
            if (sol.empty() || intervals[i][0] > sol.back()[1])
            {
                sol.push_back(intervals[i]);
            }
            else
            {
                sol.back()[1] = max(intervals[i][1], sol.back()[1]);
            }
        }
        return sol;
    }
};