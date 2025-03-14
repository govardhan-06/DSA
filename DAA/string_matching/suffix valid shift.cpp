#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Suffix Valid Shift Algorithm
// Find the longest prefix of P that is also a suffix of T[s+1 ... s+m]
// Time complexity: O(n*m), where n = |T| and m = |P|

vector<int> computeLPS(string &P)
{
    int m = P.length();
    vector<int> lps(m, 0); // LPS table for the pattern P
    int k = 0;             // longest prefix suffix length
    for (int q = 1; q < m; q++)
    {
        while (k > 0 && P[k] != P[q])
            k = lps[k - 1];
        if (P[k] == P[q])
            k++;
        lps[q] = k;
    }
    return lps;
}

int findSuffixValidShift(const string &T, const string &P)
{
    int n = T.length(), m = P.length();
    vector<int> pi = computePrefixFunction(P);
    int maxLen = 0, validShift = -1;

    // Iterate over possible shifts
    for (int s = 0; s <= n - m; s++)
    {
        string subText = T.substr(s, m); // Extract T[s+1 ... s+m]

        // Find the longest prefix of P that is also a suffix of subText
        int k = 0;
        for (int i = 0; i < m; i++)
        {
            while (k > 0 && P[k] != subText[i])
            {
                k = pi[k - 1];
            }
            if (P[k] == subText[i])
            {
                k++;
            }
        }

        // Update the first occurrence of the maximum valid shift
        if (k > maxLen)
        {
            maxLen = k;
            validShift = s;
        }
    }

    return maxLen;
}