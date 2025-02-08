#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void binarySearch(vector<int> &arr, int low, int high, int target, int &count)
{
    if (low > high)
    {
        return;
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] == target)
    {
        count++;
        return;
    }
    else if (arr[mid] > target)
    {
        binarySearch(arr, low, mid - 1, target, count);
    }
    else
    {
        binarySearch(arr, mid + 1, high, target, count);
    }
}

void searchElement(int n, vector<vector<int>> &arr, int target, int &count)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i][0] <= target && arr[i][n - 1] >= target)
        {
            binarySearch(arr[i], 0, n - 1, target, count);
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