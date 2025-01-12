#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// finding the duplicate and missing number
//  CodeNinja question
//  Time-Complexity: O(N) ; Space-Complexity: O(1)
vector<int> findMissingRepeatingNumbers(vector<int> a)
{
    int n = a.size();
    // S1-sum of all elements
    long long S1 = (n * (n + 1)) / 2;
    // S2-sum of squares of elements
    long long S2 = (n * (n + 1) * (2 * n + 1)) / 6;
    long long squares = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
        squares += (long long)a[i] * (long long)a[i];
    }
    // X-Y
    long long val1 = S1 - sum;
    // X^2-Y^2
    long long val2 = S2 - squares;
    // X+Y
    val2 = val2 / val1;
    long long x = (val1 + val2) / 2;
    long long y = x - val1;
    return {(int)y, (int)x};
}