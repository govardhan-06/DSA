#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        int n = intervals.size();
        vector<vector<int>> sol;
        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < n; i++)
        {
            int start = intervals[i][0];
            int end = intervals[i][1];
            if (!sol.empty() && end <= sol.back()[1])
            {
                continue;
            }
            for (int j = i + 1; j < n; j++)
            {
                if (intervals[j][0] <= end)
                {
                    start = min(start, intervals[j][0]);
                    end = max(end, intervals[j][1]);
                }
                else
                {
                    break;
                }
            }
            sol.push_back({start, end});
        }
        intervals = sol;
        return intervals;
    }
};