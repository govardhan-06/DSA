#include <iostream>
using namespace std;

int nCr(int n, int r)
{
    long long res = 1;
    for (int i = 0; i < r; i++)
    {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return res;
}

int pascals(int r, int c)
{
    int element = nCr(r - 1, c - 1);
    return element;
}

int main()
{
    int r = 5;
    int c = 5;
    cout << "Element at position (5,5): " << pascals(r, c);
}