#include <stdio.h>

int main(void)
{
    int t, n;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        scanf("%d", &n);
        int height[n];
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &height[j]);
        }
        int max = height[0];
        for (int k = 1; k < n; k++)
        {
            if (height[k] > max)
            {
                max = height[k];
            }
        }
        printf("%d\n", max);
    }
}
