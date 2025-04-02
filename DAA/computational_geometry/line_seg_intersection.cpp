#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
};

// Corrected direction function
int direction(Point &P1, Point &P2, Point &P3)
{
    return (P2.x - P1.x) * (P3.y - P1.y) - (P3.x - P1.x) * (P2.y - P1.y);
}

// Corrected onSegment function
bool onSegment(Point &P1, Point &P2, Point &P3)
{
    return (min(P1.x, P2.x) <= P3.x && P3.x <= max(P1.x, P2.x) &&
            min(P1.y, P2.y) <= P3.y && P3.y <= max(P1.y, P2.y));
}

// Function to check if two line segments (P1P2) and (P3P4) intersect
bool checkIntersection(Point &P1, Point &P2, Point &P3, Point &P4)
{
    int d1 = direction(P1, P2, P3);
    int d2 = direction(P1, P2, P4);
    int d3 = direction(P3, P4, P1);
    int d4 = direction(P3, P4, P2);

    // General case: The segments properly intersect
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
    {
        return true;
    }

    // Special case: Check if they are collinear and overlap
    if (d1 == 0 && onSegment(P1, P2, P3))
        return true;
    if (d2 == 0 && onSegment(P1, P2, P4))
        return true;
    if (d3 == 0 && onSegment(P3, P4, P1))
        return true;
    if (d4 == 0 && onSegment(P3, P4, P2))
        return true;

    return false; // No intersection
}

int main()
{
    Point P1, P2, P3, P4;

    cout << "Enter coordinates for first line segment (x1 y1 x2 y2): ";
    cin >> P1.x >> P1.y >> P2.x >> P2.y;

    cout << "Enter coordinates for second line segment (x3 y3 x4 y4): ";
    cin >> P3.x >> P3.y >> P4.x >> P4.y;

    if (checkIntersection(P1, P2, P3, P4))
        cout << "Segments Intersect\n";
    else
        cout << "Segments Do Not Intersect\n";

    return 0;
}
