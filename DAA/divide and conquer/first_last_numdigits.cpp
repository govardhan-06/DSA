#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// using recursion find the first and last digit of a numebr
class Solution
{
public:
    int find_FirstDigit(int n)
    {
        if (n < 10)
            return n;
        else
            return find_FirstDigit(n / 10);
    }
    int find_LastDigit(int n)
    {
        return n % 10;
    }
};

int main()
{
    Solution s;
    int n = 124563;
    cout << "First digit: " << s.find_FirstDigit(n) << "\n";
    cout << "Last digit: " << s.find_LastDigit(n);
}