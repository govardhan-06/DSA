#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to calculate the maximum profit for rod cutting
int cutRod(vector<int> &price, int n)
{
    // Step 1: Create a DP table
    vector<vector<int>> dp(n, vector<int>(n + 1, 0));

    // Step 2: Initialize base case for the first row (length 1 pieces)
    for (int N = 0; N <= n; N++)
    {
        dp[0][N] = N * price[0];
    }

    // Step 3: Fill the DP table iteratively
    for (int ind = 1; ind < n; ind++)
    {
        for (int N = 0; N <= n; N++)
        {
            // Not taking the current piece length
            int notTake = 0 + dp[ind - 1][N];

            // Taking the current piece length (if it fits)
            int take = INT_MIN;
            int rodLength = ind + 1;
            if (rodLength <= N)
            {
                take = price[ind] + dp[ind][N - rodLength];
            }

            // Store the maximum of taking or not taking
            dp[ind][N] = max(take, notTake);
        }
    }

    // Step 4: Return the result from the last cell
    return dp[n - 1][n];
}

int main()
{
    // Input: Price array for different lengths of rod
    vector<int> price = {2, 5, 7, 8};
    int n = price.size(); // Length of the rod

    // Call the function and print the result
    cout << "Maximum Profit: " << cutRod(price, n) << endl;

    return 0;
}
