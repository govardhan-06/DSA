#include <iostream>
#include <vector>
using namespace std;

// Pascals Triangle
class Solution
{
public:
    vector<int> generateRow(int r)
    {
        long long ans = 1;
        vector<int> row;
        row.push_back(1);
        for (int c = 1; c < r; c++)
        {
            ans = ans * (r - c);
            ans = ans / c;
            row.push_back(ans);
        }
        return row;
    }
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> pascals;
        for (int i = 1; i <= numRows; i++)
        {
            pascals.push_back(generateRow(i));
        }
        return pascals;
    }
};