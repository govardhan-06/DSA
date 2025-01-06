#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Merge Sorted Array - Leetcode versions
class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int n2 = 0;
        for (int i = m; i < m + n; i++)
        {
            nums1[i] = nums2[n2++];
        }
        sort(nums1.begin(), nums1.end());
    }
};