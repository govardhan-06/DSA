#include <bits/stdc++.h>
using namespace std;

// without traversing find freq of array elements
// divide and conquer

class Solution
{
public:
    void findFrequencyUtil(int arr[], int low, int high, vector<int> &freq)
    {
        // base case
        if (arr[low] == arr[high])
        {
            freq[arr[low]] += high - low + 1;
        }
        else
        {
            int mid = (low + high) / 2;
            findFrequencyUtil(arr, low, mid, freq);
            findFrequencyUtil(arr, mid + 1, high, freq);
        }
    }

    void findFrequency(int arr[], int n)
    {
        vector<int> freq(arr[n - 1] + 1, 0);
        findFrequencyUtil(arr, 0, n - 1, freq);

        for (int i = 0; i <= arr[n - 1]; i++)
            if (freq[i] != 0)
                cout << "Element " << i << " occurs " << freq[i] << " times" << endl;
    }
};

int main()
{
    int arr[] = {1, 1, 1, 2, 3, 3, 5, 5, 8, 8, 8, 9, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    Solution s;
    s.findFrequency(arr, n);
    return 0;
}
