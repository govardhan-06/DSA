#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// recursive algo using divide and conquer find the maximum digit of a number

class Solution
{
public:
    int findmaxdigits(int n)
    {
        // base case
        if (n < 10)
            return n;
        else
        {
            // Divide
            int lastDigit = n % 10;
            int remDigit = n / 10;

            int findMax_rem = findmaxdigits(remDigit);

            // Conquer
            if (lastDigit > findMax_rem)
                return lastDigit;
            else
                return findMax_rem;
        }
    }
};

int main()
{
    Solution s;
    int n = 125963;
    cout << s.findmaxdigits(n);
}