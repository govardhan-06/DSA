#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int maxCrossingSum(vector<int> &nums, int left, int mid, int right)
    {
        // Maximum sum on the left of mid
        int leftSum = INT_MIN;
        int sum = 0;
        for (int i = mid; i >= left; i--)
        {
            sum += nums[i];
            if (sum > leftSum)
            {
                leftSum = sum;
            }
        }

        // Maximum sum on the right of mid
        int rightSum = INT_MIN;
        sum = 0;
        for (int i = mid + 1; i <= right; i++)
        {
            sum += nums[i];
            if (sum > rightSum)
            {
                rightSum = sum;
            }
        }

        // Combine both sides
        return leftSum + rightSum;
    }

    int maxSubArrayHelper(vector<int> &nums, int left, int right)
    {
        // Base case: only one element
        if (left == right)
        {
            return nums[left];
        }

        int mid = left + (right - left) / 2;

        // Maximum subarray sum can be in:
        // 1. Left half
        int leftMax = maxSubArrayHelper(nums, left, mid);

        // 2. Right half
        int rightMax = maxSubArrayHelper(nums, mid + 1, right);

        // 3. Crossing the midpoint
        int crossMax = maxCrossingSum(nums, left, mid, right);

        // Return the maximum of the three
        return max({leftMax, rightMax, crossMax});
    }

    int maxSubArray(vector<int> &nums)
    {
        return maxSubArrayHelper(nums, 0, nums.size() - 1);
    }
};
