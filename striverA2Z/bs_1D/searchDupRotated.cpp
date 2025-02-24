// Problem: Search in Rotated Sorted Array II
// The array is rotated at some pivot point. The array may contain duplicates.
// You are given a target value to search. If found in the array return true, otherwise return false.
// Time complexity: O(logn) where n is the size of the array ; worst case : O(n/2) => O(n)
// Space complexity: O(1)

class Solution
{
public:
    int searchArray(vector<int> &arr, int target)
    {
        int start = 0, end = arr.size() - 1, mid = 0;
        while (start <= end)
        {
            mid = start + (end - start) / 2;
            if (arr[mid] == target)
                return mid;
            // edge case
            else if (arr[start] == arr[mid] && arr[mid] == arr[end])
            {
                start++;
                end--;
                continue;
            }
            // left subarray
            else if (arr[start] <= arr[mid])
            {
                // this case: arr[start]<=target<=arr[mid]
                if (arr[start] <= target && arr[mid] >= target)
                    end = mid - 1;
                else
                    start = mid + 1;
            }
            // right subarray
            else
            {
                // this case: arr[mid]<=target<=arr[end]]
                if (arr[mid] <= target && arr[end] >= target)
                    start = mid + 1;
                else
                    end = mid - 1;
            }
        }
        return -1;
    }
    bool search(vector<int> &nums, int target)
    {
        int res = searchArray(nums, target);
        if (res == -1)
            return false;
        return true;
    }
};