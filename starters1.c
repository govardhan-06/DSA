#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int a, b, c, m;
        scanf("%d %d %d %d", &a, &b, &c, &m);
        if (a + m == b || a + m == c || b + m == a || b + m == c || c + m == a || c + m == b)
        {
            printf("YES\n");
        }
    }
}
