#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// find the maximum difference between two numbers in an array
// largest difference will be = max-min of the array

class Solution
{
public:
    void findMaxMin(vector<int> &arr, int low, int high, int *min, int *max)
    {
        // Base case: only one element
        if (low == high)
        {
            *max = *min = arr[low];
            return;
        }

        // Base case: two elements
        if (low == high - 1)
        {
            if (arr[low] > arr[high])
            {
                *max = arr[low];
                *min = arr[high];
            }
            else
            {
                *max = arr[high];
                *min = arr[low];
            }
            return;
        }

        // Recursive case: divide and conquer
        int mid = (low + high) / 2;

        int lmin, lmax, rmin, rmax;
        findMaxMin(arr, low, mid, &lmin, &lmax);
        findMaxMin(arr, mid + 1, high, &rmin, &rmax);

        // Conquer: merge results
        if (lmin < rmin)
            *min = lmin;
        else
            *min = rmin;
        if (lmax > rmax)
            *max = lmax;
        else
            *max = rmax;
    }
};

int main()
{
    Solution s;
    vector<int> arr = {1, 2, 7, -20, 115, 142, 122};
    int minv = INT_MAX, maxv = INT_MIN;

    // Call the maxDiff function
    s.findMaxMin(arr, 0, arr.size() - 1, &minv, &maxv);

    // Output the maximum difference
    cout << "Maximum Difference: " << (maxv - minv) << endl;

    return 0;
}
