#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int fibonacci(int n, vector<int> &dp)
{
    if (n <= 1)
        return n;
    return dp[n] = fibonacci(n - 1, dp) + fibonacci(n - 2, dp);
}

int main()
{
    int n = 0;
    cin >> n;
    vector<int> dp(n + 1, -1);
    cout << fibonacci(n, dp);
}