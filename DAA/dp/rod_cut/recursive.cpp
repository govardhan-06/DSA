#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to maximize profit for rod cutting
int f(int ind, int N, vector<int> &price, vector<vector<int>> &dp)
{
    // Base case: If we are at the first length option
    if (ind == 0)
    {
        // Maximum pieces of length 1 we can take
        return N * price[0];
    }

    // If value is already computed, return it
    if (dp[ind][N] != -1)
        return dp[ind][N];

    // Not taking the current length
    int notTake = 0 + f(ind - 1, N, price, dp);

    // Taking the current length (if it fits)
    int take = INT_MIN;
    int rodLength = ind + 1;
    if (rodLength <= N)
    {
        take = price[ind] + f(ind, N - rodLength, price, dp);
    }

    // Store and return the maximum of both options
    return dp[ind][N] = max(take, notTake);
}

// Function to initialize DP table and start the recursion
int cutRod(vector<int> &price, int n)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return f(n - 1, n, price, dp);
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
