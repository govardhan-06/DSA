#include <bits/stdc++.h>
using namespace std;

// Moore's Voting Algorithm
// The algorithm is based on the fact that the majority element will
// always be present in the array if the count of the majority element is greater than n/2.
// Time complexity: O(n)
// Space complexity: O(1)

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        int el = 0;
        int n = nums.size();
        int count = 0;
        // applying the moore's voting algorithm
        for (int i = 0; i < n; i++)
        {
            if (count == 0)
            {
                el = nums[i];
                count++;
            }
            else if (nums[i] == el)
                count++;
            else
                count--;
        }
        int check_count = 0;
        // checking if the element is majority element or not
        // if the last found element is the majority element then it will returned
        // else -1 will be returned
        // in some cases, there may not be any majority element
        // eg: [1, 2, 3, 4, 5]
        for (int i = 0; i < n; i++)
        {
            if (nums[i] == el)
            {
                check_count++;
            }
        }
        if (check_count > n / 2)
            return el;
        return -1;
    }
};