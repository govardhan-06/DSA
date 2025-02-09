#include <bits/stdc++.h>
using namespace std;

// Time complexity: O(log(m*n))
// Space complexity: O(1)

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int low = 0;
        int m = matrix.size(), n = matrix[0].size();
        int high = m * n - 1;
        int mid = low + (high - low) / 2;
        while (low <= high)
        {
            if (matrix[mid / n][mid % n] == target)
                return true;
            else if (matrix[mid / n][mid % n] > target)
                high = mid - 1;
            else if (matrix[mid / n][mid % n] < target)
                low = mid + 1;
            mid = low + (high - low) / 2;
        }
        return false;
    }
};