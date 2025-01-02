#include <stdio.h>
#include <stdbool.h>

// Chcek array is sorted and rotated
bool check(int *nums, int numsSize)
{
    int x = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] > nums[(i + 1) % numsSize])
        {
            x++;
        }
    }
    if (x > 1)
    {
        return false;
    }
    return true;
}