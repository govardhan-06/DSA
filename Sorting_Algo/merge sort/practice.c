#include <stdio.h>

void merge(int a[], int low, int mid, int high)
{
    int size = high - low + 1;
    int tmp[size];
    int c = 0;
    int left = low;
    int right = mid + 1;

    // Merging both the arrays after comparing the left and right pointer-pointed elements
    while (left <= mid && right <= high)
    {
        if (a[left] < a[right])
        {
            tmp[c++] = a[left++];
        }
        else
        {
            tmp[c++] = a[right++];
        }
    }

    // Adding the remaining elements from the arrays to the temporary array
    while (left <= mid)
    {
        tmp[c++] = a[left++];
    }

    while (right <= high)
    {
        tmp[c++] = a[right++];
    }

    // Adding the elements to the main array
    for (int i = 0; i < size; i++)
    {
        a[low + i] = tmp[i];
    }
}

void mergeSort(int a[], int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int mid = (low + high) / 2;
    mergeSort(a, low, mid);
    mergeSort(a, mid + 1, high);
    merge(a, low, mid, high);
}

int main()
{
    int n = 5;
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    mergeSort(arr, 0, n - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
