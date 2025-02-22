#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Longest Arithmetic Progression Sequence
// Time Complexity: O(n^2)
// Space Complexity: O(n^2)

int longestAP(vector<int> &arr)
{
    int n = arr.size();
    // If the size of the array is less than or equal to 2, then the answer will be the size of the array
    if (n <= 2)
        return n;
    int ans = 0;
    unordered_map<int, int> dp[n + 1];
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int diff = arr[i] - arr[j];
            int count = 1;
            if (dp[j].find(diff) != dp[j].end())
            {
                count = dp[j][diff];
            }
            dp[i][diff] = 1 + count;
            ans = max(ans, dp[i][diff]);
        }
    }
    return ans;
}

int main()
{
    vector<int> arr = {6, 10, 9, 12};
    cout << longestAP(arr) << endl;
    return 0;
}