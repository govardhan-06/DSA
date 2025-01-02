#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);
        int a[n];

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }

        int first_max = -1, second_max = -1;

        for (int i = 0; i < n; i++)
        {
            if (a[i] > first_max)
            {
                second_max = first_max;
                first_max = a[i];
            }
            else if (a[i] > second_max && a[i] != first_max)
            {
                second_max = a[i];
            }
        }

        int sum = first_max + second_max;

        printf("%d\n", sum);
    }

    return 0;
}
