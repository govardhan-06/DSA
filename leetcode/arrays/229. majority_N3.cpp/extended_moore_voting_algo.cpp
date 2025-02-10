#include <bits/stdc++.h>
using namespace std;

// Extended Moore's Voting Algorithm
// Time complexity: O(n)
// Space complexity: O(1)

class Solution
{
public:
    vector<int> majorityElement(vector<int> &nums)
    {
        int el1 = INT_MAX, el2 = INT_MAX;
        int count1 = 0, count2 = 0;
        vector<int> results;

        // apply moore's voting algorithm
        for (int i = 0; i < nums.size(); i++)
        {
            // if the new element is different from el2 then it is a new candidate for el1
            if (count1 == 0 && nums[i] != el2)
            {
                count1 = 1;
                el1 = nums[i];
            }
            // if the new element is different from el1 then it is a new candidate for el2
            else if (count2 == 0 && nums[i] != el1)
            {
                count2 = 1;
                el2 = nums[i];
            }
            else if (nums[i] == el1)
                count1++;
            else if (nums[i] == el2)
                count2++;
            else
            {
                count1--;
                count2--;
            }
        }
        int c1 = 0, c2 = 0;

        // check if the elements are majority elements
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == el1)
                c1++;
            if (nums[i] == el2)
                c2++;
        }
        if (c1 > nums.size() / 3)
            results.push_back(el1);
        if (c2 > nums.size() / 3)
            results.push_back(el2);
        sort(results.begin(), results.end());
        return results;
    }
};