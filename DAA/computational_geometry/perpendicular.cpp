// Perpendicular Line Segments
// Let S be a set of n line segments in two dimensional planes. Design an algorithm to count the number of pairs of line segments which are perpendicular. Your algorithm should not use the division operation and trigonometric functions. Cartesian coordinates of the end points of the line segment are given. For example,  n= 3 line segments are

// 0  0      0 2

// 0 0      1 0

//  0 0     1 1

//  The ouput of your program  should be1

// Input Format:

// Enter the number of lines.

// Enter the end points of each line

// Output Format:

// Number of line segments which are perpendicular.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void checkPerpendicular(int n, vector<pair<int, int>> &points)
{
    vector<pair<int, int>> lines;
    for (int i = 0; i < 2 * n; i += 2)
    {
        int dx = points[i + 1].first - points[i].first;
        int dy = points[i + 1].second - points[i].second;
        lines.push_back({dx, dy});
    }
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int dx1 = lines[i].first, dy1 = lines[i].second;
            int dx2 = lines[j].first, dy2 = lines[j].second;
            if (dx1 * dx2 + dy1 * dy2 == 0)
                count++;
        }
    }
    cout << count;
}

int main()
{
    int n = 0;
    cin >> n;
    vector<pair<int, int>> points(2 * n);
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> points[i].first >> points[i].second;
    }
    checkPerpendicular(n, points);
}