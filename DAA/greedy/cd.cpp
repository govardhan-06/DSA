#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// CD Fit Problem
// Given a list of songs with their durations and the maximum capacity of a CD, find the minimum number of CDs required to store all the songs.
// The songs can be stored in any order and the songs cannot be split.
// Time Complexity: O(nlogn)

int findCDs(vector<int> &songs, int maxCap)
{
    int n = songs.size();
    int cdCount = 0;
    int remSpace = maxCap;
    sort(songs.begin(), songs.end());
    for (int i = 0; i < n; i++)
    {
        if (songs[i] <= remSpace)
        {
            remSpace -= songs[i];
        }
        else
        {
            cdCount++;
            remSpace = maxCap - songs[i];
        }
    }
    return cdCount + 1;
}

int main()
{
    vector<int> songs = {4, 7, 3, 2, 5, 4};
    int maxCap = 10;
    cout << findCDs(songs, maxCap) << endl;
    return 0;
}