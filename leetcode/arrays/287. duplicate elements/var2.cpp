#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Sorting and finding duplicate
// Time complexity: O(nlogn+n)  ;  Space complexity: O(1)
class Solution
{
public:
    int findDup(vector<int> nums)
    {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i] == nums[i + 1])
            {
                return nums[i];
            }
        }
        return -1;
    }
};

int main()
{
    Solution s;
    vector<int> arr = {1, 5, 3, 6, 2};
    int num = s.findDup(arr);
    cout << "Duplicate Element: " << num << "\n";
}