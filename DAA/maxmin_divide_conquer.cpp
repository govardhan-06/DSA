#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution
{
public:
    void maxmin(vector<int> &arr, int i, int j, int *max, int *min)
    {
        // Base Case: with one element in the array
        if (i == j)
        {
            *max = arr[i];
            *min = arr[i];
            return;
        }
        // Base Case: with two elements in the array
        else if (i == j - 1)
        {
            if (arr[i] > arr[j])
            {
                *max = arr[i];
                *min = arr[j];
            }
            else
            {
                *max = arr[j];
                *min = arr[i];
            }
            return;
        }

        // divide
        int mid = (i + j) / 2;
        // left sub-array
        maxmin(arr, i, mid, max, min);
        int lmin = *min, lmax = *max;
        // right sub-array
        maxmin(arr, mid + 1, j, max, min);
        int rmin = *min, rmax = *max;

        // conquer
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
    int max = INT_MIN, min = INT_MAX;
    vector<int> arr = {0, 0};
    int n = arr.size();
    s.maxmin(arr, 0, n - 1, &max, &min);
    cout << "Maximum Element of the Array: " << max << "\n";
    cout << "Minimum Element of the Array: " << min << "\n";
}
