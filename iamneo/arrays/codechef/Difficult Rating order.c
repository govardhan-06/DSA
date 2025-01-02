#include <stdio.h>

int main()
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        int n;
        scanf("%d", &n);
        int d[n];

        for (int i = 0; i < n; i++)
        {
            scanf("%d", &d[i]);
        }

        int c = 0;

        for (int i = 0; i < n; i += 2)
        {
            if (d[i] > d[i + 1])
            {
                c = 1;
                break;
            }
        }

        if (c == 1)
        {
            printf("No\n");
        }
        else
        {
            printf("Yes\n");
        }
    }
}
