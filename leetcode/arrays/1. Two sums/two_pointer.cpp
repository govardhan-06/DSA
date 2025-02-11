#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Two Sums
// Here it returns the pair of numbers which makes the sum equal to target
// To get the indices, we need to sort the array with the indices
// like {(1, 0), (2, 1), (3, 2), (4, 3), (5, 4)} where the first element is the number and the second element is the index
// but that approach is not optimal
// Time Complexity: O(nlogn + n) => O(nlogn)
// Space Complexity: O(1)

class Solution
{
public:
    vector<int> twoSums(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int low = 0, high = nums.size() - 1;
        while (low < high)
        {
            if (nums[low] + nums[high] == target)
            {
                return {low, high};
            }
            else if (nums[low] + nums[high] < target)
            {
                low++;
            }
            else
            {
                high--;
            }
        }
        return {-1, -1};
    }
};

int main()
{
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> res = s.twoSums(nums, target);
    cout << res[0] << " " << res[1] << endl;
    return 0;
}