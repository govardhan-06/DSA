#include <stdio.h>

int maxFinder(int a[], int n)
{
    int max = a[0];
    for (int i = 0; i < n; i++)
    {
        if (max < a[i])
        {
            max = a[i];
        }
    }
    return max;
}

int countingSort(int a[], int n)
{
    int key = maxFinder(a, n);
    int count[key + 1];
    for (int i = 0; i < key + 1; i++)
    {
        count[i] = 0;
    }
    int b[n];
    for (int i = 0; i < n; i++)
    {
        count[a[i]]++;
    }
    for (int i = 1; i < key + 1; i++)
    {
        count[i] = count[i] + count[i - 1];
    }
    for (int i = 0; i < n; i++)
    {
        b[--count[a[i]]] = a[i];
    }
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    countingSort(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}