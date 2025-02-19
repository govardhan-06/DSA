#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Activity Selection Problem
// Given a list of activities with their start and finish times, we need to select the maximum number of activities that can be
// performed by a single person, assuming that a person can only work on a single activity at a time.
// Time complexity: O(nlogn+n) = O(nlogn)
// Space complexity: O(1)

bool activityCompare(pair<int, int> a, pair<int, int> b)
{
    return a.second < b.second;
}

int activitySelection(vector<pair<int, int>> &activities, int n)
{
    sort(activities.begin(), activities.end(), activityCompare);
    int count = 1;
    int lastActivity = 0;
    cout << activities[0].first << " " << activities[0].second << endl;
    for (int i = 1; i < n; i++)
    {
        if (activities[i].first >= activities[lastActivity].second)
        {
            count++;
            cout << activities[i].first << " " << activities[i].second << endl;
            lastActivity = i;
        }
    }
    return count;
}

int main()
{
    vector<pair<int, int>> activities = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
    int n = activities.size();
    cout << "Maximum number of activities that can be performed: " << activitySelection(activities, n) << endl;
}