class Solution
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        int start = 0, end = nums.size() - 1;
        int mid = start + (end - start) / 2;
        int newIndex = 0;
        while (start <= end)
        {
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
            {
                newIndex = mid + 1;
                start = mid + 1;
            }
            else
                end = mid - 1;
            mid = start + (end - start) / 2;
        }
        return newIndex;
    }
};