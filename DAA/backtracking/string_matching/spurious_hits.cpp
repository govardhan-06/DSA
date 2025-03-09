#include <iostream>
#include <vector>

using namespace std;

// Compute determinant of a 2x2 matrix directly
inline int findDet(int a, int b, int c, int d)
{
    return a * d - b * c;
}

// Function to check if two matrices are equal
bool matrixEqual(vector<vector<int>> &T, int i, int j, vector<vector<int>> &P)
{
    for (int x = 0; x < P.size(); x++)
    {
        for (int y = 0; y < P[0].size(); y++)
        {
            if (T[i + x][j + y] != P[x][y])
            {
                return false;
            }
        }
    }
    return true;
}

// Find spurious hits using optimized determinant calculation
vector<pair<int, int>> findSpuriousHits(vector<vector<int>> &T, vector<vector<int>> &P)
{
    int n = T.size();
    int m = P.size();
    int detP = findDet(P[0][0], P[0][1], P[1][0], P[1][1]);

    vector<pair<int, int>> spuriousHits;

    for (int i = 0; i <= n - m; i++)
    { // Iterate over row start points
        for (int j = 0; j <= n - m; j++)
        { // Iterate over column start points
            // Compute determinant of 2x2 submatrix from T
            int detT = findDet(T[i][j], T[i][j + 1], T[i + 1][j], T[i + 1][j + 1]);

            if (detT == detP)
            { // Potential match
                if (!matrixEqual(T, i, j, P))
                {                                           // Check full matrix equality only if needed
                    spuriousHits.push_back({i + 1, j + 1}); // Convert to 1-based indexing
                }
            }
        }
    }

    return spuriousHits;
}

int main()
{
    int n, m;
    cin >> n;

    // Read matrix T
    vector<vector<int>> T(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> T[i][j];
        }
    }

    cin >> m;

    // Read matrix P
    vector<vector<int>> P(m, vector<int>(m));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> P[i][j];
        }
    }

    // Find spurious hits
    vector<pair<int, int>> spuriousHits = findSpuriousHits(T, P);

    // Print result
    if (spuriousHits.empty())
    {
        cout << "0" << endl;
    }
    else
    {
        for (auto &hit : spuriousHits)
        {
            cout << "(" << hit.first << "," << hit.second << ") ";
        }
        cout << endl;
    }

    return 0;
}
