#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// merge sorted array without extra space - optimal sol - 1
class Solution
{
public:
    void merge(long long arr1[], int m, long long arr2[], int n)
    {
        int x = m - 1;
        int y = 0;
        while (x >= 0 && y < n)
        {
            if (arr1[x] > arr2[y])
            {
                swap(arr1[x], arr2[y]);
                x--;
                y++;
            }
            else
            {
                break;
            }
        }
        sort(arr1, arr1 + m);
        sort(arr2, arr2 + n);
    }
};

int main()
{
    long long arr1[] = {1, 3, 5, 7};
    long long arr2[] = {0, 2, 6, 8, 4};
    Solution s;
    s.merge(arr1, 4, arr2, 5);
    for (int i : arr1)
    {
        cout << i << " ";
    }
    cout << "\n";
    for (int j : arr2)
    {
        cout << j << " ";
    }
    cout << "\n";
}