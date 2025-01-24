#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// square root of a number using recursion and divide and conquer

class Solution
{
public:
    int findsqrt(int low, int high, int n, int &result)
    {
        // base case: returning the largest value of mid for which mid^2<=n
        // the floor of root(n) basically
        if (low > high)
            return result;
        int mid = (low + high) / 2;
        if (mid * mid == n)
            return mid;         // Perfect square case
        else if (mid * mid < n) // search the upper half
        {
            result = mid;
            return findsqrt(mid + 1, high, n, result);
        }
        else // search the lower half
        {
            return findsqrt(low, mid - 1, n, result);
        }
    }

    int findsqrt_n(int n)
    {
        int result;
        if (n == 1 || n == 0)
            return n;
        return findsqrt(0, n / 2, n, result);
    }
};

int main()
{
    Solution s;
    cout << s.findsqrt_n(1002);
}