#include <bits/stdc++.h>
using namespace std;

// Given an array of size n, find the majority element.
// The majority element is the element that appears more than n/2 times.
// Time complexity: O(nlogn) + O(n) = O(nlogn)
// Space complexity: O(n)

class Solution
{
public:
    int majority(vector<int> &arr)
    {
        map<int, int> mp;
        for (int i = 0; i < arr.size(); i++)
        {
            mp[arr[i]]++;
        }
        for (auto it : mp)
        {
            if (it.second > arr.size() / 2)
            {
                return it.first;
            }
        }
        return -1;
    }
};

int main()
{
    Solution s;
    vector<int> arr = {1, 2, 3, 4, 5, 5, 5, 5, 5};
    cout << s.majority(arr) << endl;
}