#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// Arithmetic text algorithm
// shifts are in arthimetic progression

vector<int> computeLPS(string &P)
{
    int m = P.length();
    vector<int> lps(m, 0);
    int k = 0;
    for (int q = 1; q < m; q++)
    {
        while (k > 0 && P[k] != P[q])
        {
            k = lps[k - 1];
        }
        if (P[k] == P[q])
        {
            k++;
        }
        lps[q] = k;
    }
    return lps;
}

vector<int> KMP(string &T, string &P)
{
    int n = T.length();
    int m = P.length();
    vector<int> lps = computeLPS(P);
    vector<int> shifts;
    int q = 0;
    for (int i = 0; i < n; i++)
    {
        while (q > 0 && P[q] != T[i])
        {
            q = lps[q - 1];
        }
        if (P[q] == T[i])
        {
            q++;
        }
        if (q == m)
        {
            shifts.push_back(i - m + 1);
            q = lps[q - 1];
        }
    }
    return shifts;
}

void check_Arthimetic_Text(string &T, string &P)
{
    vector<int> shifts = KMP(T, P);
    if (shifts.size() == 0)
    {
        cout << "Pattern not found in the text" << endl;
    }
    else
    {
        cout << "Pattern found at shifts: ";
        int common_diff = shifts[1] - shifts[0];
        cout << shifts[0] << " ";
        int flag = 1;
        for (int i = 1; i < shifts.size(); i++)
        {
            int currDiff = shifts[i] - shifts[i - 1];
            if (currDiff != common_diff)
            {
                flag = 0;
            }
            cout << shifts[i] << " ";
        }
        cout << endl;
        if (flag)
        {
            cout << "Pattern is an arithmetic progression" << endl;
        }
        else
        {
            cout << "Pattern is not an arithmetic progression" << endl;
        }
    }
}

int main()
{
    string T = "ABABDABACDABABCABAB";
    string P = "AB";
    check_Arthimetic_Text(T, P);
    return 0;
}