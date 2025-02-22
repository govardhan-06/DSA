#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// nQueens Problem
// Time Complexity: O(n!)
// Space Complexity: O(n^2)
// check hashing.md for more details

void solve(int col, vector<string> &board, vector<vector<string>> &ans, vector<int> leftRow, vector<int> upperDiagonal, vector<int> lowerDiagonal, int n)
{
    if (col == n)
    {
        ans.push_back(board);
        return;
    }
    for (int row = 0; row < n; row++)
    {
        if (leftRow[row] == 0 && upperDiagonal[(n - 1) + (col - row)] == 0 && lowerDiagonal[row + col] == 0)
        {
            board[row][col] = 'Q';
            leftRow[row] = 1;
            upperDiagonal[row - col + (n - 1)] = 1;
            lowerDiagonal[row + col] = 1;
            solve(col + 1, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
            board[row][col] = '.';
            leftRow[row] = 0;
            upperDiagonal[row - col + (n - 1)] = 0;
            lowerDiagonal[row + col] = 0;
        }
    }
}

vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> ans;
    vector<string> board(n);
    string s(n, '.');
    for (int i = 0; i < n; i++)
    {
        board[i] = s;
    }
    vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
    solve(0, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
    return ans;
}

int main()
{
    int n = 5;
    vector<vector<string>> ans;
    ans = solveNQueens(n);
    for (auto i : ans)
    {
        for (auto j : i)
        {
            cout << j << endl;
        }
        cout << endl;
    }
}