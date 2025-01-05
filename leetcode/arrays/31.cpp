#include <iostream>
using namespace std;
#include <vector>
#include <algorithm> //for using fn like reverse(),swap()

// Next Permututation
class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int ind = -1;
        int n = nums.size();
        for (int i = n - 2; i >= 0; i--)
        {
            if (nums[i] < nums[i + 1])
            {
                ind = i;
                break;
            }
        }
        if (ind == -1)
        { // edge case
            reverse(nums.begin(), nums.end());
            return;
        }
        for (int i = n - 1; i >= ind; i--)
        {
            if (nums[i] > nums[ind])
            {
                swap(nums[i], nums[ind]);
                break;
            }
        }
        reverse(nums.begin() + ind + 1, nums.end());
    }
};