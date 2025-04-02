#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
    bool isLeft;      // True if it is a left endpoint of a segment
    int segmentIndex; // Index of the segment in the original list
};

// Structure to represent a segment
struct Segment
{
    Point left, right;
};

// Comparator for sorting events
bool comparePoints(const Point &p1, const Point &p2)
{
    if (p1.x != p2.x)
        return p1.x < p2.x;
    if (p1.isLeft != p2.isLeft)
        return p1.isLeft; // Left endpoints before right endpoints
    return p1.y < p2.y;   // Sort by y if x is the same
}

// Function to check if two segments intersect
bool doIntersect(Segment s1, Segment s2)
{
    auto direction = [](Point a, Point b, Point c)
    {
        return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    };

    int d1 = direction(s1.left, s1.right, s2.left);
    int d2 = direction(s1.left, s1.right, s2.right);
    int d3 = direction(s2.left, s2.right, s1.left);
    int d4 = direction(s2.left, s2.right, s1.right);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;

    return false;
}

// Custom comparator for set (ordered by y-coordinate)
struct CompareY
{
    bool operator()(const int &idx1, const int &idx2) const
    {
        return idx1 < idx2; // This will be replaced by segment comparison
    }
};

// Plane Sweep Algorithm for segment intersection
bool anySegmentIntersect(vector<Segment> &segments)
{
    vector<Point> events;

    for (int i = 0; i < segments.size(); i++)
    {
        events.push_back({segments[i].left.x, segments[i].left.y, true, i});
        events.push_back({segments[i].right.x, segments[i].right.y, false, i});
    }

    sort(events.begin(), events.end(), comparePoints);

    set<int, CompareY> T; // Active segments sorted by y-coordinate

    for (auto &p : events)
    {
        int idx = p.segmentIndex;
        if (p.isLeft)
        { // Left endpoint
            auto it = T.lower_bound(idx);
            if (it != T.end() && doIntersect(segments[idx], segments[*it]))
                return true;
            if (it != T.begin() && doIntersect(segments[idx], segments[*prev(it)]))
                return true;

            T.insert(idx);
        }
        else
        { // Right endpoint
            auto it = T.find(idx);
            auto above = next(it);
            auto below = it != T.begin() ? prev(it) : T.end();

            if (above != T.end() && below != T.end() && doIntersect(segments[*above], segments[*below]))
                return true;

            T.erase(it);
        }
    }
    return false;
}

// Main function
int main()
{
    int n;
    cout << "Enter number of segments: ";
    cin >> n;
    vector<Segment> segments(n);

    cout << "Enter the segments (x1 y1 x2 y2):\n";
    for (int i = 0; i < n; i++)
    {
        cin >> segments[i].left.x >> segments[i].left.y >> segments[i].right.x >> segments[i].right.y;
        if (segments[i].left.x > segments[i].right.x)
            swap(segments[i].left, segments[i].right);
    }

    if (anySegmentIntersect(segments))
        cout << "Intersection found!\n";
    else
        cout << "No intersections.\n";

    return 0;
}
