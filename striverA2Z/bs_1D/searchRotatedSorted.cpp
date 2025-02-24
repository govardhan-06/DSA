class Solution
{
public:
    int search(vector<int> &arr, int target)
    {
        int start = 0, end = arr.size() - 1, mid = 0;
        while (start <= end)
        {
            mid = start + (end - start) / 2;
            if (arr[mid] == target)
                return mid;
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
};