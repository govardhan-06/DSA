#include <iostream>
#include <vector>
using namespace std;

// Kadane Algo
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int len = nums.size();
        int max = INT_MIN;
        int sum = 0;
        int start = 0;
        int ansStart = 0;
        int ansEnd = 0;
        for (int i = 0; i < len; i++)
        {
            if (sum == 0)
                start = i;
            sum += nums[i];
            if (sum > max)
            {
                max = sum;
                ansStart = start;
                ansEnd = i;
            }
            if (sum < 0)
            {
                sum = 0;
            }
        }
        return max;
        // at last print the array from the index ansStart to ansEnd to get the maximum subArray
    }
};