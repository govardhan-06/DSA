#include <bits/stdc++.h>
using namespace std;

// pow(x,n)
// Implement pow(x, n), which calculates x raised to the power n (i.e., xn).
// x - double & n - integer
// Difficulty in this question: Chances of overflow are there, so we need to handle that.
//  Time complexity: O(log(n))
//  Space complexity: O(1)

class Solution
{
public:
    double myPow(double x, int n)
    {
        if (n == 0)
            return 1;
        double ans = 1.0;
        long long nn = n;
        if (n < 0)
            nn = -1 * nn;
        while (nn != 0)
        {
            if (nn % 2 == 0)
            {
                x *= x;
                nn /= 2;
            }
            else
            {
                ans *= x;
                nn -= 1;
            }
        }
        if (n < 0)
            ans = (double)(1.0) / (double)(ans);
        return ans;
    }
};