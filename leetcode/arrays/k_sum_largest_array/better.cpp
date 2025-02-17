#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// Largest subarray with sum k
// Given an array of integers, find the largest subarray with sum k.
// Time complexity: O(nlogn)
// Space complexity: O(n)

// optimal for negative numbers and positive numbers (no zeros)
// better solution for positive numbers and zeros

int largestSubArraySum(vector<int> &arr, long long k)
{
    map<long long, int> mp;
    long long sum = 0;
    int n = arr.size();
    int maxLen = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
        if (sum == k)
            maxLen = i + 1;
        long long rem = sum - k;
        if (mp.find(rem) != mp.end())
            maxLen = max(maxLen, i - mp[rem]);
        if (mp.find(sum) == mp.end())
            mp[sum] = i;
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