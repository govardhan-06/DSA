// Find the frequency of an element in a sorted rotated array
// Time Complexity: O(logn)
// Space Complexity: O(1)

class Solution
{
public:
    int firstOccur(vector<int> &nums, int target)
    {
        int low = 0, high = nums.size() - 1, mid = 0;
        int index = -1;
        while (low <= high)
        {
            if (nums[mid] == target)
            {
                index = mid;
                high = mid - 1;
            }
            else if (nums[low] <= nums[mid])
            {
                if (nums[low] <= target && target <= nums[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            else
            {
                if (nums[mid] <= target && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return index;
    }
    int lastOccur(vector<int> &nums, int target)
    {
        int low = 0, high = nums.size() - 1, mid = 0;
        int index = -1;
        while (low <= high)
        {
            if (nums[mid] == target)
            {
                index = mid;
                low = mid + 1;
            }
            else if (nums[low] <= nums[mid])
            {
                if (nums[low] <= target && target <= nums[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            else
            {
                if (nums[mid] <= target && target <= nums[high])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
        }
        return index;
    }
    bool search(vector<int> &nums, int target)
    {
        int findex = firstOccur(nums, target);
        int lindex = lastOccur(nums, target);
        if (findex == -1)
            return -1;
        return lindex - findex + 1;
    }
};