#include <bits/stdc++.h>

class Solution
{
public:
    vector<int> majorityElement(vector<int> &nums)
    {
        map<int, int> mp;
        vector<int> results;
        for (int i = 0; i < nums.size(); i++)
        {
            mp[nums[i]]++;
        }
        for (auto it : mp)
        {
            if (it.second > nums.size() / 3)
                results.push_back(it.first);
        }
        return results;
    }
};