#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to compute the minimum number of scalar multiplications
void MatrixChainOrder(vector<int> &p, vector<vector<int>> &m, vector<vector<int>> &s)
{
    int n = p.size() - 1; // Number of matrices
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0; // Base case: Single matrix cost is 0
    }

    // l is the chain length
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++)
            {
                // Compute cost
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (q < m[i][j])
                {
                    m[i][j] = q; // Store minimum multiplication cost
                    s[i][j] = k; // Store optimal split point
                }
            }
        }
    }
}

// Function to print the optimal parenthesization
void PrintOptimalParenthesis(vector<vector<int>> &s, int i, int j)
{
    if (i == j)
    {
        cout << "A" << i;
    }
    else
    {
        cout << "(";
        PrintOptimalParenthesis(s, i, s[i][j]);
        PrintOptimalParenthesis(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main()
{
    vector<int> p = {40, 20, 30, 10, 30}; // Example matrix dimensions
    int n = p.size() - 1;                 // Number of matrices

    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0));

    MatrixChainOrder(p, m, s);

    cout << "Minimum number of multiplications: " << m[1][n] << endl;
    cout << "Optimal Parenthesization: ";
    PrintOptimalParenthesis(s, 1, n);
    cout << endl;

    return 0;
}
