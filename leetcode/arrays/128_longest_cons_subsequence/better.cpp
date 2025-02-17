#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Problem: Longest Consecutive Subsequence
// Approach: Sorting and Linear Traversal
// Time complexity: O(nlogn)
// Space complexity: O(1)

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        sort(nums.begin(), nums.end());
        int count = 0;
        int lastSmall = INT_MIN;
        int longest = 1;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] - 1 == lastSmall)
            {
                count++;
                lastSmall = nums[i];
            }
            else if (nums[i] != lastSmall)
            {
                count = 1;
                lastSmall = nums[i];
            }
            longest = max(longest, count);
        }
        return longest;
    }
};