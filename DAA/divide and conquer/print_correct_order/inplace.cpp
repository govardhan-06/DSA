#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution
{
public:
    int findCorrect(vector<int> &arr, int low, int high, int &index)
    {
        if (low > high)
            return 0;
        if (low == high)
        {
            if (index == 0 || arr[high] > arr[index - 1])
            {
                // in-place modification
                arr[index++] = arr[high];
            }
            return 0;
        }
        else
        {
            int mid = (low + high) / 2;
            findCorrect(arr, low, mid, index);      // left subarray
            findCorrect(arr, mid + 1, high, index); // right subarray
            return 0;
        }
    }
};

int main()
{
    Solution s;
    vector<int> arr = {1, 3, 2, 0, 4, 5};
    int index = 0;
    s.findCorrect(arr, 0, arr.size() - 1, index);
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}