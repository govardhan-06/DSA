#include <bits/stdc++.h>
using namespace std;

// Reverse Pairs
// Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2 * nums[j].
// Time Compelxity: O(2nlogn) <- merge sort + count pairs
// Space Complexity: O(n) <- merge sort

class Solution
{
public:
    int countPairs(vector<int> &nums, int low, int mid, int high)
    {
        int right = mid + 1;
        int count = 0;
        for (int i = low; i <= mid; i++)
        {
            while (right <= high && nums[i] > 2LL * nums[right])
            {
                right++;
            }
            count += (right - (mid + 1));
        }
        return count;
    }
    void mergeSplitPair(vector<int> &nums, int low, int mid, int high)
    {
        int i = low, j = mid + 1;
        vector<int> temp;
        while (i <= mid && j <= high)
        {
            if (nums[i] < nums[j])
            {
                temp.push_back(nums[i]);
                i++;
            }
            else
            {
                temp.push_back(nums[j]);
                j++;
            }
        }
        while (i <= mid)
        {
            temp.push_back(nums[i++]);
        }
        while (j <= high)
        {
            temp.push_back(nums[j++]);
        }
        for (int i = 0; i < temp.size(); i++)
        {
            nums[low + i] = temp[i];
        }
    }
    int mergePair(vector<int> &nums, int low, int high, int &count)
    {
        if (low >= high)
            return 0;
        int mid = low + (high - low) / 2;
        mergePair(nums, low, mid, count);
        mergePair(nums, mid + 1, high, count);
        count += countPairs(nums, low, mid, high);
        mergeSplitPair(nums, low, mid, high);
        return 1;
    }
    int reversePairs(vector<int> &nums)
    {
        int count = 0;
        mergePair(nums, 0, nums.size() - 1, count);
        return count;
    }
};