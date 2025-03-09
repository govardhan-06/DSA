#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minPlatforms(vector<double> &arrival, vector<double> &departure)
{
    sort(arrival.begin(), arrival.end());
    sort(departure.begin(), departure.end());
    int n = arrival.size(), i = 0, j = 0;
    int currentPlatforms = 0, maxPlatforms = 0;
    // maxPlatforms will store the maximum number of platforms required at any time
    // currentPlatforms will store the number of platforms required at the current time
    while (i < n && j < n)
    {
        if (arrival[i] <= departure[j])
        {
            currentPlatforms++;
            i++;
            maxPlatforms = max(maxPlatforms, currentPlatforms);
        }
        else
        {
            currentPlatforms--;
            j++;
        }
    }
    return maxPlatforms;
}

int main()
{
    vector<double> arrival = {9.00, 9.40, 9.10, 11.00, 15.00, 18.00};
    vector<double> departure = {9.10, 12.00, 9.20, 11.30, 19.00, 20.00};
    cout << "Minimum platforms required: " << minPlatforms(arrival, departure) << endl;
    return 0;
}