#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to calculate the maximum profit for rod cutting
int cutRod(vector<int> &price, int n)
{
    // Step 1: Create two 1D DP arrays
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    // Step 2: Initialize base case for the first row (length 1 pieces)
    for (int N = 0; N <= n; N++)
    {
        prev[N] = N * price[0];
    }

    // Step 3: Fill the DP table using prev and curr
    for (int ind = 1; ind < n; ind++)
    {
        for (int N = 0; N <= n; N++)
        {
            // Not taking the current piece length
            int notTake = 0 + prev[N];

            // Taking the current piece length (if it fits)
            int take = INT_MIN;
            int rodLength = ind + 1;
            if (rodLength <= N)
            {
                take = price[ind] + curr[N - rodLength];
            }

            // Store the maximum of taking or not taking
            curr[N] = max(take, notTake);
        }

        // Step 4: Copy current row to previous row
        prev = curr;
    }

    // Step 5: Return the result from the last element of prev
    return prev[n];
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
