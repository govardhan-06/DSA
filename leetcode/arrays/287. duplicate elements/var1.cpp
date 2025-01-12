#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Duplicate element in array
//  Time complexity: O(n) ; Space complexity: O(n)
class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        // Intialising a vector in C++
        vector<int> count(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++)
        {
            count[nums[i]]++;
        }
        for (int i = 0; i < count.size(); i++)
        {
            if (count[i] > 1)
            {
                return i;
            }
        }
        return 0;
    }
};