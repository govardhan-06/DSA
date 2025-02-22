#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// nQueens Problem
// Time Complexity: O(n!*n)
// Space Complexity: O(n^2)
// check basic.md for more details

// function to check if the current position is safe or not
bool isSafe(int row, int col, vector<string> &board, int n)
{
    // check the upper diagonal
    int duprow = row, dupcol = col;
    while (row >= 0 & col >= 0)
    {
        if (board[row][col] == 'Q')
            return false;
        row--;
        col--;
    }

    // check the left row(same row case)
    row = duprow;
    col = dupcol;
    while (col >= 0)
    {
        if (board[row][col] == 'Q')
            return false;
        col--;
    }

    // check the lower diagonal
    // row = duprow;  <- since we are not manipulating row in the previous loop, we can use the same row value
    col = dupcol;
    while (row < n && col >= 0)
    {
        if (board[row][col] == 'Q')
            return false;
        row++;
        col--;
    }
    return true;
}

// function to find each board configuration satisfying the nQueens problem and adding it to the ans vector
void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n)
{
    // if we have reached the last column, then we have found a valid configuration
    if (col == n)
    {
        ans.push_back(board);
        return;
    }
    // for each row in the current column, we check if the current position is safe or not
    // we will take a col, and then iterate over all the rows and fix the queen at that position and then move to the next column
    for (int row = 0; row < n; row++)
    {
        if (isSafe(row, col, board, n))
        {
            board[row][col] = 'Q';
            // if the current position is safe, then we move to the next column(recursion)
            solve(col + 1, board, ans, n);
            // backtracking step - removing the queen from the current position so that we can try the next row to avoid duplicates
            board[row][col] = '.';
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
    solve(0, board, ans, n);
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