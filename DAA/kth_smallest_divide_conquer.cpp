#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Finding the kth smallest element from the array using recursion stack
// Time Complexity: O(n) (Average Case) {Worst case: O(n^2)}
// Space Complexity: O(1) {For recursion stack: O(logn) to O(n) <- usually ignored}

class Solution
{
public:
    // Partition function
    int partition(vector<int> &arr, int low, int high)
    {
        int pivot = arr[low];
        int plow = low + 1, phigh = high; // Adjust plow and phigh initialization
        while (plow <= phigh)
        {
            while (plow <= high && arr[plow] <= pivot) // Ensure plow stays within bounds
                plow++;
            while (phigh >= low + 1 && arr[phigh] >= pivot) // Ensure phigh stays within bounds
                phigh--;
            if (plow < phigh)
            {
                swap(arr[plow], arr[phigh]);
            }
        }
        swap(arr[low], arr[phigh]); // Place the pivot in its correct position
        return phigh;
    }

    // Recursive function to find the kth smallest element
    int kth_small(vector<int> &arr, int low, int high, int k)
    {
        if (low <= high)
        {
            int pindex = partition(arr, low, high);
            if (pindex == k)
                return arr[pindex];
            else if (pindex < k)
                return kth_small(arr, pindex + 1, high, k);
            else
                return kth_small(arr, low, pindex - 1, k);
        }
        return -1; // Return -1 if the element is not found
    }
};

int main()
{
    Solution s;
    vector<int> arr = {7, 2, 14, 10, 1, 80};
    int k = 5; // kth smallest element (k-1 for 0-based index)
    cout << "Required element: " << s.kth_small(arr, 0, arr.size() - 1, k - 1) << endl;
    return 0;
}
