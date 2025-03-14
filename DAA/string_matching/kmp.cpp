#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Knuth-Morris-Pratt algorithm

// Compute the prefix function of a string
vector<int> computePrefixFunction(const string &P)
{
    int m = P.length();
    vector<int> lps(m, 0); // Prefix array initialized to 0
    int k = 0;             // Length of the longest prefix-suffix

    for (int q = 1; q < m; q++)
    { // Start from index 1 (0-based indexing)
        while (k > 0 && P[k] != P[q])
        {
            k = lps[k - 1]; // Move k back to the previous best prefix
        }
        if (P[k] == P[q])
        {
            k++; // Increase k if characters match
        }
        lps[q] = k; // Store the prefix function value
    }

    // NOTE
    // Last element of lps array(lps[n-1]) will store the length of
    // longest prefix that is also suffix of entire string

    return lps;
}

// KMP string matching algorithm
void KMPSearch(const string &T, const string &P)
{
    int n = T.length();
    int m = P.length();
    vector<int> lps = computePrefixFunction(P);

    int q = 0; // Number of characters matched

    for (int i = 0; i < n; i++)
    { // Iterate over the text (0-based indexing)
        while (q > 0 && P[q] != T[i])
        {
            q = lps[q - 1]; // Move q back using the prefix function
        }
        if (P[q] == T[i])
        {
            q++; // Move to the next character
        }
        if (q == m)
        { // Pattern found
            cout << "Pattern occurs with shift " << (i - m + 1) << endl;
            q = lps[q - 1]; // Look for the next match
        }
    }
}

int main()
{
    string T = "ABABDABACDABABCABAB";
    string P = "AB";
    KMPSearch(T, P);
    return 0;
}