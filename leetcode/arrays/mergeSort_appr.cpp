#include <bits/stdc++.h>

// Coding Ninjas
//  Count the number of inversions in an array.
//  An inversion is defined as a pair of indices (i, j) such that i < j and arr[i] > arr[j].

// Brute force approach
// Directly use two loops to check for the condition of inversion.
// Time complexity: O(n^2)
// Space complexity: O(1)

// Optimal approach (this one)
// Use merge sort to count the number of inversions.
// Time complexity: O(nlogn)
// Space complexity: O(n)

long long mergeCount(long long *arr, int low, int mid, int high)
{
    int i = low, j = mid + 1;
    vector<long long> temp;
    int invCount = 0;
    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            temp.push_back(arr[i++]);
        else
        {
            temp.push_back(arr[j++]);
            invCount += (mid - i + 1);
        }
    }
    while (i <= mid)
    {
        temp.push_back(arr[i++]);
    }
    while (j <= high)
    {
        temp.push_back(arr[j++]);
    }
    for (int i = 0; i < high - low + 1; i++)
    {
        arr[low + i] = temp[i];
    }
    return invCount;
}
long long mergeSort(long long *arr, int low, int high)
{
    if (low >= high)
        return 0;
    int mid = low + (high - low) / 2;
    int lcount = mergeSort(arr, low, mid);
    int rcount = mergeSort(arr, mid + 1, high);
    int scount = mergeCount(arr, low, mid, high);
    return lcount + rcount + scount;
}
long long getInversions(long long *arr, int n)
{
    return mergeSort(arr, 0, n - 1);
}