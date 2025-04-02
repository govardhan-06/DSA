#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x, y;
};

// Function to determine the orientation of three points
int direction(Point p1, Point p2, Point p3)
{
    int res = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if (res == 0)
        return 0;             // Collinear points
    return (res > 0) ? 1 : 2; // 1 = Counterclockwise, 2 = Clockwise
}

vector<Point> jarvisMarch(vector<Point> &points)
{
    int n = points.size();
    if (n < 3)
        return {}; // Convex hull is not possible with <3 points

    vector<Point> hull;

    // Step 1: Find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++)
    {
        if (points[i].x < points[leftmost].x)
        {
            leftmost = i;
        }
    }

    // Step 2: Start wrapping around the hull
    int p = leftmost, q;
    do
    {
        hull.push_back(points[p]); // Add the current point to the hull
        q = (p + 1) % n;           // Assume the next point is the next in the list

        for (int i = 0; i < n; i++)
        {
            // If i is more counterclockwise than q, update q
            if (direction(points[p], points[i], points[q]) == 1)
            {
                q = i;
            }
        }

        p = q; // Move to the next hull point
    } while (p != leftmost); // Stop when we complete the hull

    return hull;
}

// Driver code for testing
int main()
{
    vector<Point> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    vector<Point> hull = jarvisMarch(points);

    cout << "Convex Hull Points:\n";
    for (auto p : hull)
    {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
