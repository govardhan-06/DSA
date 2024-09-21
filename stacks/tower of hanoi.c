// During an archaeological expedition, a team discovers the "Disk of Light," an artifact consisting of concentric rings with unique symbols. To unlock its powers, they must perform the "Tower of Wisdom" ritual.

// In this ritual:

// There are three pedestals: Source (A), Auxiliary (B), and Illuminated (C).
// Disks are stacked on the Source pedestal, smaller ones on top of larger ones.
// Only one disk can be moved at a time.
// A disk can only be placed on top of a larger disk or an empty pedestal.

// Write a program to assist the archaeological team in calculating the total number of times each ring of the Disk of Light is moved during the Tower of Wisdom ritual.

// Input format :
// The input consists of an integer denoting the number of disks.

// Output format :
// The output displays the sequence of moves required to solve the puzzle.

// The last line of output displays the total number of times the disk is moved.

// Refer to the sample output for formatting specifications.

// Code constraints :
// 1 ≤ n ≤ 8

// Sample test cases :
// Input 1 :
// 3
// Output 1 :
// Move disk 1 from A to C
// Move disk 2 from A to B
// Move disk 1 from C to B
// Move disk 3 from A to C
// Move disk 1 from B to A
// Move disk 2 from B to C
// Move disk 1 from A to C
// Total number of times the disk is moved: 7

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
