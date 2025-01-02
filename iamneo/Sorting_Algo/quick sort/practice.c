#include <stdio.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[low]; // Choose the first element as the pivot
    int i = low;        // Initialize the left pointer
    int j = high;       // Initialize the right pointer

    while (i < j) // Continue until the pointers meet
    {
        while (a[i] <= pivot && i < high) // Move the left pointer to the right until an element greater than pivot is found
        {
            i++;
        }
        while (a[j] > pivot) // Move the right pointer to the left until an element less than or equal to pivot is found
        {
            j--;
        }
        if (i < j) // If the pointers have not crossed, swap the elements
        {
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[low], &a[j]); // Place the pivot in its correct position
    return j;             // Return the pivot index
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int pIndex = partition(a, low, high); // gets the pivot index
        quickSort(a, low, pIndex - 1);        // recursive sorting of left subarray
        quickSort(a, pIndex + 1, high);       // recursive sorting of right subarray
    }
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

    quickSort(arr, 0, n - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
