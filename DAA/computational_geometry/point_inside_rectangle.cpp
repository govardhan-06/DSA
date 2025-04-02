// Check if a point is inside the rectangle
// given the vertices of recatngles P,Q,R,S and point T
// check if point T is inside the rectangle or not

// Solution
// Use cross product to check if point T is inside the rectangle or not
// If the cross product of vectors PT and PR is positive, then point T is inside the rectangle
// If the cross product of vectors PT and PR is negative, then point T is outside the rectangle
// If the cross product of vectors PT and PR is zero, then point T is on the rectangle

#include <iostream>
#include <algorithm>
#include <utility> // for std::pair
using namespace std;

double crossProduct(pair<double, double> A, pair<double, double> B, pair<double, double> C)
{
    return (B.first - A.first) * (C.second - A.second) - (B.second - A.second) * (C.first - A.first);
}

int onSegment(pair<double, double> A, pair<double, double> B, pair<double, double> C)
{
    return (
        min(A.first, B.first) <= C.first && C.first <= max(A.first, B.first) &&
        min(B.second, A.second) <= C.second && C.second <= max(A.second, B.second));
}

int main()
{
    pair<double, double> P, Q, R, S, T;
    cin >> P.first >> P.second;
    cin >> Q.first >> Q.second;
    cin >> R.first >> R.second;
    cin >> S.first >> S.second;
    cin >> T.first >> T.second;

    double cross1 = crossProduct(P, Q, T);
    double cross2 = crossProduct(Q, R, T);
    double cross3 = crossProduct(R, S, T);
    double cross4 = crossProduct(S, P, T);

    if (cross1 > 0 && cross2 > 0 && cross3 > 0 && cross4 > 0)
    {
        cout << "Point T is inside the rectangle" << endl;
    }
    else if (cross1 < 0 || cross2 < 0 || cross3 < 0 || cross4 < 0)
    {
        cout << "Point T is outside the rectangle" << endl;
    }
    else
    {
        if (onSegment(P, Q, T) || onSegment(Q, R, T) || onSegment(R, S, T) || onSegment(S, P, T))
        {
            cout << "Point T is on the rectangle" << endl;
        }
        else
        {
            cout << "Point T is outside the rectangle" << endl;
        }
    }
}