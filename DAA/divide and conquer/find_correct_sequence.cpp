#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution
{
public:
    void findIncreasingSeq(vector<int> arr, int low, int high, vector<int> &results)
    {
        // base case 1
        if (low > high)
            return;

        // base case 2 : only one element case
        if (low == high)
        {
            if (results.empty() || arr[high] > results.back())
                results.push_back(arr[high]); // add the element to the results array if the sequence is followed
            return;
        }

        int mid = (low + high) / 2;

        // left subarray
        findIncreasingSeq(arr, low, mid, results);

        // right subarray
        findIncreasingSeq(arr, mid + 1, high, results);
    }
};

int main()
{
    Solution s;
    vector<int> arr = {1, 3, 2, 5, -1, 10, 11, 15, 8};
    vector<int> results;
    s.findIncreasingSeq(arr, 0, arr.size() - 1, results);
    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i] << " ";
    }
    cout << "\n";
}