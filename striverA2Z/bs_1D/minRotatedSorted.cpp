#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Minimum element in a rotated sorted array
// Time Complexity: O(logn)
// Space Complexity: O(1)
// Further Optimization: If the array is already sorted, return the first element

int findMin(vector<int> &arr)
{
    int low = 0, high = arr.size() - 1;
    int ans = INT_MAX;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        // Further Optimization
        // if (arr[low] <= arr[high])
        // {
        //     ans = min(ans, arr[low]);
        //     break;
        // }
        if (arr[low] <= arr[mid])
        {
            ans = min(ans, arr[low]);
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
            ans = min(ans, arr[mid]);
        }
    }
    return ans;
}

int main()
{
    vector<int> arr = {4, 5, 6, 0, 1, 2};
    cout << findMin(arr);
}