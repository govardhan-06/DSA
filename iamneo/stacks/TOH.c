#include <stdio.h>

void tower(int n, char source, char dest, char aux, int *c)
{
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n", source, dest);
        (*c)++;
        return;
    }
    tower(n - 1, source, aux, dest, c);
    printf("Move disk %d from %c to %c\n", n, source, dest);
    (*c)++;
    tower(n - 1, aux, dest, source, c);
}

int main()
{
    int n = 0, count = 0;
    scanf("%d", &n);
    tower(n, 'A', 'C', 'B', &count);

    printf("Total number of times the disk is moved: %d\n", count);
    return 0;
}
