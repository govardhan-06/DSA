#include <bits/stdc++.h>
using namespace std;

// Two approaches:
//  1. Recursive which takes O(2^n)
//  2. Matrix Exponentiation O(log n)

// Matrix Exponentiation method

class Solution
{
public:
    void matrixMult(vector<vector<int>> &mat1, vector<vector<int>> &mat2)
    {
        // Performing matrix multiplication
        int x = mat1[0][0] * mat2[0][0] + mat1[0][1] * mat2[1][0];
        int y = mat1[0][0] * mat2[0][1] + mat1[0][1] * mat2[1][1];
        int z = mat1[1][0] * mat2[0][0] + mat1[1][1] * mat2[1][0];
        int w = mat1[1][0] * mat2[0][1] + mat1[1][1] * mat2[1][1];

        mat1[0][0] = x;
        mat1[0][1] = y;
        mat1[1][0] = z;
        mat1[1][1] = w;
    }

    void matrixExponent(vector<vector<int>> &mat1, int n)
    {
        if (n <= 1)
            return;

        vector<vector<int>> mat2 = {{1, 1}, {1, 0}};

        // Recursively find mat1^(n/2)
        matrixExponent(mat1, n / 2);

        // Square mat1
        matrixMult(mat1, mat1);

        // If n is odd, multiply mat1 by mat2
        if (n % 2 != 0)
            matrixMult(mat1, mat2);
    }

    int nthfibo(int n)
    {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;

        vector<vector<int>> mat1 = {{1, 1}, {1, 0}};

        matrixExponent(mat1, n - 1);

        return mat1[0][0];
    }
};

int main()
{
    Solution s;
    int n = 5;
    cout << "The " << n << "th Fibonacci number is: " << s.nthfibo(n) << endl;
    return 0;
}
