#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution
{
public:
    int binarySearch(vector<int> &arr, int low, int high, int x)
    {
        int mid = low + (high - low) / 2;

        // base case
        if (arr[mid] == x)
            return mid;

        else if (arr[mid] > x)
        {
            return binarySearch(arr, low, mid - 1, x);
        }

        else
        {
            return binarySearch(arr, mid + 1, high, x);
        }

        return -1;
    }
};

int main()
{
    Solution s;
    vector<int> arr = {0, 1, 3, 6, 10};
    int x = 10;
    cout << "Index position: " << s.binarySearch(arr, 0, arr.size(), x) + 1;
}