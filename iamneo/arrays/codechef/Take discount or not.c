#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n, x, y;
        scanf("%d %d %d", &n, &x, &y);
        int a[n];

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }
        int costWithoutDiscount = 0;
        for (int i = 0; i < n; i++)
        {
            costWithoutDiscount += a[i];
        }
        int costWithDscount = x;
        for (int i = 0; i < n; i++)
        {
            if (a[i] > y)
            {
                costWithDscount += (a[i] - y);
            }
        }
        if (costWithDscount < costWithoutDiscount)
        {
            printf("COUPON\n");
        }
        else
        {
            printf("NO COUPON\n");
        }
    }

    return 0;
}
