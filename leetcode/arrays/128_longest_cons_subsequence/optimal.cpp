#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// Problem: Longest Consecutive Subsequence
// Approach: Using Hashing
// Time complexity: O(n)
// Space complexity: O(n)

// Insertion and search in unordered_set is O(1) on average
// So, the time complexity of the solution is O(n)

class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        unordered_set<int> st;
        // Time complexity: O(n)
        for (int i = 0; i < n; i++)
        {
            st.insert(nums[i]);
        }
        int longest = 1;
        // Time complexity: O(2n)
        for (auto it : st)
        {
            // Start the count process only if the element is the start of the sequence
            if (st.find(it - 1) == st.end())
            {
                int count = 1;
                int x = it;
                // Count the number of elements in the sequence
                while (st.find(x + 1) != st.end())
                {
                    x = x + 1;
                    count++;
                }
                longest = max(longest, count);
            }
        }
        return longest;
    }
};