#include <iostream>
#include <vector>

using namespace std;

// Function to merge two halves and count inversions
int mergeAndCount(vector<int> &arr, int low, int mid, int high)
{
    int size = high - low + 1;
    vector<int> temp(size); // Temporary array for merging
    int i = low, j = mid + 1, k = 0;
    int inversionCount = 0;

    // Merge the two subarrays while counting inversions
    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            inversionCount += (mid - i + 1); // Count inversions
        }
    }

    // Copy remaining elements of the left subarray
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of the right subarray
    while (j <= high)
    {
        temp[k++] = arr[j++];
    }

    // Copy the merged array back to the original array
    for (int i = 0; i < size; i++)
    {
        arr[low + i] = temp[i];
    }

    return inversionCount;
}

// Function to perform merge sort and count inversions
int mergeSortAndCount(vector<int> &arr, int low, int high)
{
    if (low >= high)
    {
        return 0; // Base case: no inversions if the subarray has 1 or fewer elements
    }

    int mid = low + (high - low) / 2;

    // Count inversions in the left subarray
    int leftCount = mergeSortAndCount(arr, low, mid);

    // Count inversions in the right subarray
    int rightCount = mergeSortAndCount(arr, mid + 1, high);

    // Count split inversions during merge step
    int splitCount = mergeAndCount(arr, low, mid, high);

    // Total inversions is the sum of left, right, and split inversions
    return leftCount + rightCount + splitCount;
}

int main()
{
    vector<int> arr = {8, 4, 2, 1};

    // Get the total inversion count
    int n = arr.size();
    int inversionCount = mergeSortAndCount(arr, 0, n - 1);

    // Output the sorted array and inversion count
    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Total Inversions: " << inversionCount << endl;

    return 0;
}
