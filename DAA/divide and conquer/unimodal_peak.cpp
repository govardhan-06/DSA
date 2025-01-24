#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution
{
public:
    int findpeak(vector<int> &arr, int low, int high)
    {
        int mid = low + (high - low) / 2; // handles overflows in case of large numbers
        // mid=(low+high)/2  --> usual approach for finding mid

        // base case
        // handles the edges cases where the array:
        // Has only one element and other situations like array- :
        // 1. Continously increases
        // 2. Continously decreases
        if ((mid == 0 || arr[mid] > arr[mid - 1]) && (mid == arr.size() - 1 || arr[mid] > arr[mid + 1]))
            return arr[mid]; // peak point

        else if (mid > 0 && arr[mid] < arr[mid - 1]) // search the lower half
            return findpeak(arr, low, mid - 1);
        else // search the upper half
            return findpeak(arr, mid + 1, high);
    }
};

int main()
{
    Solution s;
    vector<int> arr = {4, 5, 6, 7, 11, 10, 9, 8, 7, 3, 2, 1};
    cout << s.findpeak(arr, 0, arr.size() - 1);
}