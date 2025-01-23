#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// find the occurence of an element in the array using divide and conquer
class Solution
{
public:
    int findOccurence(vector<int> &arr, int low, int high, int x)
    {
        // base case
        if (low == high)
        {
            if (arr[low] == x)
                return 1;
            return 0;
        }
        else
        {
            int mid = (low + high) / 2;
            return findOccurence(arr, low, mid, x) + findOccurence(arr, mid + 1, high, x);
        }
    }
};

int main()
{
    Solution s;
    vector<int> arr = {4, 5, 8, 1, 25, 4, 4, 0, 4};
    int x = 4;
    cout << s.findOccurence(arr, 0, arr.size(), x);
}