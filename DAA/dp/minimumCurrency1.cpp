#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int minCurr(int cost, vector<vector<int>> &currNotes)
{
    int n = currNotes.size();
    vector<vector<int>> dp(n + 1, vector<int>(cost + 1, INT_MAX)); // dp[i][j] stores min notes required to make j using first i rows
    dp[0][0] = 0;                                                  // Base case: 0 notes required to make cost 0

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= cost; j++)
        {
            if (dp[i - 1][j] != INT_MAX)
            {
                // normal iteration
                // instead use: k: 0 to currNotes[i-1].size()
                // instead of note: currNotes[i-1][k]
                for (int note : currNotes[i - 1])
                {
                    if (j + note <= cost)
                    {
                        dp[i][j + note] = min(dp[i][j + note], dp[i - 1][j] + 1);
                    }
                }
            }
        }
    }

    return (dp[n][cost] == INT_MAX) ? -1 : dp[n][cost]; // Return -1 if cost is not achievable
}

int main()
{
    int cost = 11;
    vector<vector<int>> currNotes = {
        {1, 2, 5},
        {1, 3, 4},
        {2, 3, 5}};

    cout << "Minimum notes required: " << minCurr(cost, currNotes) << endl;
    return 0;
}
