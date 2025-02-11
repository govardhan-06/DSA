#include <bits/stdc++.h>
using namespace std;

// Two Sums
// Problem: Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// Time Complexity: O(nlogn)
// for unordered_map: O(1) but then its worst case is O(n^2)
// Space Complexity: O(n)

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        map<int, int> mp;
        for (int i = 0; i < nums.size(); i++)
        {
            int a = nums[i];
            int more = target - a;
            if (mp.find(more) != mp.end())
            {
                return {mp[more], i};
            }
            mp[a] = i;
        }
        return {-1, -1};
    }
};