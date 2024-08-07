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

        int ops = 0;
        int min = a[0];

        for (int i = 0; i < n; i++)
        {
            if (min > a[i])
            {
                min = a[i];
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (a[i] != min)
            {
                ops++;
            }
        }

        printf("%d\n", ops);
    }

    return 0;
}
