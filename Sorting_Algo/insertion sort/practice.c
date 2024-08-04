#include <stdio.h>

void insertionSort(int a[], int len)
{
    for (int i = 0; i <= len - 1; i++)
    {
        int j = i;
        while (j > 0 && a[j] < a[j - 1])
        {
            int temp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = temp;
            j--;
        }
    }
    for (int i = 0; i < len; i++)
    {
        printf("%d ", a[i]);
    }
}

int main()
{
    int n = 5;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    insertionSort(arr, n);
}