#include <iostream>
using namespace std;
#include <vector>

// Dutch National Flag Algorithm
class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int len = nums.size();
        int low = 0, mid = 0, high = len - 1;
        while (mid <= high)
        {
            if (nums[mid] == 0)
            {
                swap(nums[mid], nums[low]);
                low++;
                mid++;
            }
            else if (nums[mid] == 1)
            {
                mid++;
            }
            else
            {
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
};