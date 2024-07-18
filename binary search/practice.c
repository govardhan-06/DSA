#include <stdio.h>

int binarySearch(int arr[], int size, int key)
{
    int start = 0;
    int end = size - 1;
    int mid_value = start + (end - start) / 2;
    while (start <= end)
    {
        if (arr[mid_value] == key)
        {
            return mid_value;
        }
        if (arr[mid_value] < key)
        { // key is greater than the mid value
            start = mid_value + 1;
        }
        else
        { // key is less than the mid value
            end = mid_value - 1;
        }
        mid_value = start + (end - start) / 2;
    }
    return -1;
}

int main()
{
    int arr[5] = {1, 2, 3, 6, 10};
    int arr1[8] = {2, 5, 6, 8, 9, 10, 23, 65};

    printf("The index of 6 in array 1: %d \n", binarySearch(arr, 5, 6));
    printf("The index of 65 in array 2: %d", binarySearch(arr1, 8, 65));
}