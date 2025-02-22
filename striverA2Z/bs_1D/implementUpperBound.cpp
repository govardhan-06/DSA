//{ Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User code template

class Solution
{
public:
    vector<int> getFloorAndCeil(int x, vector<int> &arr)
    {
        sort(arr.begin(), arr.end());
        int start = 0, end = arr.size() - 1;
        int mid = start + (end - start) / 2;
        int floorValue = -1, ceilValue = -1;
        while (start <= end)
        {
            if (arr[mid] == x)
                return {arr[mid], arr[mid]};
            else if (arr[mid] < x)
            {
                floorValue = arr[mid];
                start = mid + 1;
            }
            else
            {
                ceilValue = arr[mid];
                end = mid - 1;
            }
            mid = start + (end - start) / 2;
        }
        return {floorValue, ceilValue};
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore the newline character after t
    while (t--)
    {
        vector<int> arr;
        int x;
        string input;
        cin >> x;
        cin.ignore();

        getline(cin, input); // Read the entire line for the array elements
        stringstream ss(input);
        int number;
        while (ss >> number)
        {
            arr.push_back(number);
        }

        Solution ob;
        auto ans = ob.getFloorAndCeil(x, arr);
        cout << ans[0] << " " << ans[1] << "\n~\n";
    }
    return 0;
}
// } Driver Code Ends