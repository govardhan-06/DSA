#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Example 1:
// Input:
// n = 4
// target = 4
// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// 13 14 15 16

void searchElement(int n, vector<vector<int>> &arr, int target, int &count)
{
    int low = 0, high = n * n - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        int row = mid / n;
        int col = mid % n;
        if (arr[row][col] == target)
        {
            count++;
            return;
        }
        else if (arr[row][col] > target)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
}

int main()
{
    int n = 0;
    cin >> n;
    int target = 0;
    cin >> target;
    int count = 0;
    vector<vector<int>> arr(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
    searchElement(n, arr, target, count);
    cout << count << endl;
}