//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
public:
    int findFloor(vector<int> &arr, int k)
    {
        int start = 0, end = arr.size() - 1;
        int mid = start + (end - start) / 2;
        int resultIndex = -1;
        while (start <= end)
        {
            if (arr[mid] == k)
                return mid;
            else if (arr[mid] < k)
            {
                resultIndex = mid;
                start = mid + 1;
            }
            else
                end = mid - 1;
            mid = start + (end - start) / 2;
        }
        return resultIndex;
    }
};

//{ Driver Code Starts.
int main()
{
    string ts;
    getline(cin, ts);
    int t = stoi(ts);
    while (t--)
    {

        vector<int> arr;
        string input;
        getline(cin, input);
        stringstream ss(input);
        int number;
        while (ss >> number)
        {
            arr.push_back(number);
        }
        string ks;
        getline(cin, ks);
        int k = stoi(ks);
        Solution ob;
        int ans = ob.findFloor(arr, k);

        cout << ans << endl;
    }
    return 0;
}
// } Driver Code Ends