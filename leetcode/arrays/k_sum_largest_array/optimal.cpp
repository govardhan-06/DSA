#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Largest sum of subarray of size k
// Time complexity: O(2n)
// Space complexity: O(1)

// optimal solution for array with positive integers and zeros

int largestSubArraySum(vector<int> &nums, long long k)
{
    int maxLen = 0;
    long long sum = nums[0];
    int n = nums.size();
    int left = 0, right = 0; // Two pointers
    while (right < n)
    {
        while (left <= right && sum > k)
        {
            sum -= nums[left];
            left++;
        }
        if (sum == k)
        {
            maxLen = max(maxLen, right - left + 1);
        }
        right++;
        if (right < n)
            sum += nums[right];
    }
    return maxLen;
}

int main()
{
    vector<int> arr = {10, 5, 2, 7, 1, 9};
    long long k = 15;
    cout << largestSubArraySum(arr, k) << endl;
    return 0;
}