#include <stdio.h>

void bubbleSort(int a[], int len)
{
    for (int i = len - 1; i >= 0; i--)
    {
        int didSwap = 0; // optimisation
        for (int j = 0; j <= i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                didSwap = 1;
            }
        }
        if (didSwap == 0) // optimisation
        {
            break;
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
    bubbleSort(arr, n);
}