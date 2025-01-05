#include <iostream>
using namespace std;
#include <vector>

class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int len = nums.size();
        int c0 = 0, c1 = 0, c2 = 0;
        for (int i = 0; i < len; i++)
        {
            if (nums[i] == 0)
                c0++;
            else if (nums[i] == 1)
                c1++;
            else
                c2++;
        }
        for (int i = 0; i < c0; i++)
        {
            nums[i] = 0;
        }
        for (int i = c0; i < c0 + c1; i++)
        {
            nums[i] = 1;
        }
        for (int i = c0 + c1; i < len; i++)
        {
            nums[i] = 2;
        }
    }
};