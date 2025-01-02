#include <stdio.h>

int main()
{
    int N, X;
    scanf("%d %d", &N, &X);

    int found = 0; // Flag to indicate if X is found
    for (int i = 0; i < N; i++)
    {
        int element;
        scanf("%d", &element);
        if (element == X)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

    return 0;
}