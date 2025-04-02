#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Function to compute orientation
int direction(Point p1, Point p2, Point p3) {
    int res = ((p2.x - p1.x) * (p3.y - p1.y)) - ((p3.x - p1.x) * (p2.y - p1.y));
    if (res > 0) return 1;  // Counter-clockwise
    else if (res < 0) return 2;  // Clockwise
    return 0;  // Collinear
}

// Comparator to sort points by lowest y-coordinate (and x if equal)
bool compareByY(Point a, Point b) {
    return (a.y < b.y) || ((a.y == b.y) && (a.x < b.x));
}

// Comparator to sort by polar angle with respect to p0
bool compareByPolarAngle(Point p1, Point p2, Point p0) {
    int dxn = direction(p0, p1, p2);
    if (dxn == 0) {
        return (p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y)
             < (p2.x - p0.x) * (p2.x - p0.x) + (p2.y - p0.y) * (p2.y - p0.y);
    }
    return (dxn == 1);
}

// Function implementing Graham's Scan Algorithm
vector<Point> grahamScan(vector<Point> points) {
    int n = points.size();
    if (n < 3) return {};  // Convex hull is not possible

    // Step 1: Find the lowest y-coordinate point (pivot)
    Point p0 = *min_element(points.begin(), points.end(), compareByY);

    // Step 2: Sort points by polar angle with respect to p0
    sort(points.begin(), points.end(), [&](Point p1, Point p2) {
        return compareByPolarAngle(p1, p2, p0);
    });

    // Step 3: Convex Hull Construction using a Stack
    stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for (int i = 3; i < n; i++) {
        while (hull.size() > 1) {
            Point top = hull.top();
            hull.pop();
            Point nextTop = hull.top();

            if (direction(nextTop, top, points[i]) != 1) continue;

            hull.push(top);
            break;
        }
        hull.push(points[i]);
    }

    // Step 4: Convert Stack to Vector
    vector<Point> result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }
    
    reverse(result.begin(), result.end());  // Reverse for correct order
    return result;
}

// Driver Code
int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                            {0, 0}, {1, 2}, {3, 1}, {3, 3}};

    vector<Point> hull = grahamScan(points);

    cout << "Convex Hull Points:" << endl;
    for (auto p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }
    return 0;
}
