#include <bits/stdc++.h>

using namespace std;
int findDuplicate(vector<int> &nums)
{
    // slow and fast pointers
    int slow = nums[0];
    int fast = nums[0];
    do
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    // resetting fast pointer to intial position
    fast = nums[0];
    while (slow != fast)
    {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}
int main()
{
    vector<int> arr;
    arr = {1, 3, 4, 2, 3};
    cout << "The duplicate element is " << findDuplicate(arr) << endl;
}