#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution
{
public:
    void find_max_sum(vector<int> &arr, int low, int high, int *left_index,
                      int *right_index, int *sum)
    {
        // Base Case
        if (low == high)
        {
            *left_index = low;
            *right_index = high;
            *sum = arr[low];
            return;
        }
        else
        {
            int mid = (low + high) / 2;
            find_max_sum(arr, low, mid, left_index, right_index, sum);
            int lsub_l_index = *left_index;
            int lsub_r_index = *right_index;
            int l_sum = *sum;
            find_max_sum(arr, mid + 1, high, left_index, right_index, sum);
            int rsub_l_index = *left_index;
            int rsub_r_index = *right_index;
            int r_sum = *sum;
            find_max_cross_sum(arr, low, mid, high, left_index, right_index, sum);
            int cross_l_index = *left_index;
            int cross_r_index = *right_index;
            int cross_sum = *sum;

            if (l_sum > r_sum && l_sum > cross_sum)
            {
                *left_index = lsub_l_index;
                *right_index = lsub_r_index;
                *sum = l_sum;
                return;
            }

            else if (r_sum > l_sum && r_sum > cross_sum)
            {
                *left_index = rsub_l_index;
                *right_index = rsub_r_index;
                *sum = r_sum;
                return;
            }

            else
            {
                *left_index = cross_l_index;
                *right_index = cross_r_index;
                *sum = cross_sum;
                return;
            }
        }
    }

    void find_max_cross_sum(vector<int> &arr, int low, int mid, int high,
                            int *left_index, int *right_index, int *sum)
    {
        int left_sum = INT_MIN;
        int right_sum = INT_MIN;

        int max_left = -1;
        int max_right = -1;

        int sum_arr = 0;

        for (int i = mid; i >= low; i--)
        {
            sum_arr += arr[i];
            if (sum_arr > left_sum)
            {
                left_sum = sum_arr;
                max_left = i;
            }
        }
        sum_arr = 0;
        for (int i = mid + 1; i <= high; i++)
        {
            sum_arr += arr[i];
            if (sum_arr > right_sum)
            {
                right_sum = sum_arr;
                max_right = i;
            }
        }

        *left_index = max_left;
        *right_index = max_right;
        *sum = left_sum + right_sum;
        return;
    }
};

int main()
{
    Solution s;
    vector<int> arr = {2, 1, 6, 3, 8, 0};
    int *left_index = new int;
    int *right_index = new int;
    int *sum = new int;
    s.find_max_sum(arr, 0, arr.size() - 1, left_index, right_index, sum);
    cout << "Left index: " << *left_index << "\n";
    cout << "Right index: " << *right_index << "\n";
    cout << "Sum: " << *sum << "\n";
}