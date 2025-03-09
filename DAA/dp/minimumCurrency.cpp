#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Minimum Currency Notes Problem
// Given a cost and an array of currency notes, we have to find the minimum number of notes required to make the given cost
// Constraints: You cannot pick more than one note from same row ; You can freely avoid picking a note from one row
// Tabulation DP Approach
// Time Complexity: O((n^2)*cost)
// Space Complexity: O(cost)

int minCurrency(int cost, vector<vector<int>> &currNotes)
{
    int n = currNotes.size();
    vector<int> dp(cost + 1, INT_MAX); // dp[i] stores the minimum number of notes required to make i cost
    dp[0] = 0;                         // Base case: 0 notes required to make 0 cost

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = cost; k >= currNotes[i][j]; k--)
            {
                if (dp[k - currNotes[i][j]] != INT_MAX)
                {
                    dp[k] = min(dp[k], dp[k - currNotes[i][j]] + 1);
                }
            }
        }
    }

    if (dp[cost] == INT_MAX)
        return -1;

    return dp[cost];
}

int main()
{
    int cost = 11;
    vector<vector<int>> currNotes = {{1, 2, 5}, {1, 3, 4}, {2, 3, 5}};
    cout << minCurrency(cost, currNotes) << endl;
    return 0;
}