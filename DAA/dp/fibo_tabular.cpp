#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;
    int prev = 0, current = 1;
    for (int i = 2; i <= n; i++)
    {
        int c = prev + current;
        prev = current;
        current = c;
    }
    cout << current;
}