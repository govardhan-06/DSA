#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Largest subarray with 0 sum
// Given an array having both positive and negative integers. The task is to compute the length of the largest subarray with sum 0.
// Time complexity: O(nlogn)
// Space complexity: O(n)

class Solution
{
public:
    int maxLen(vector<int> &arr)
    {
        int maxi = 0;
        int n = arr.size();
        unordered_map<int, int> mp;
        int sum = 0;
        for (int i = 0; i < n; i++)
        {
            sum += arr[i];
            // If sum is 0, then the subarray is from 0 to i
            if (sum == 0)
                maxi = i + 1;
            else
            {
                // If sum is already present in the map, then the subarray is from mp[sum] to i
                if (mp.find(sum) != mp.end())
                {
                    maxi = max(maxi, i - mp[sum]);
                }
                // If sum is not present in the map, then add it to the map
                else
                {
                    mp[sum] = i;
                }
            }
        }
        return maxi;
    }
};