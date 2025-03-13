// C++ program for implementation of KMP pattern searching
// algorithm

#include <bits/stdc++.h>
using namespace std;
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

void computeLPSArray(string &pat, int M, vector<int> &lps);

// Prints occurrences of pat[] in txt[]
int KMPSearch(string &pat, string &txt)
{
    int M = pat.size();
    int N = txt.size();

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    vector<int> lps(M, 0);

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
    int i = 0;   // index for txt[]
    int j = 0;   // index for pat[]
    int cnt = 0; // to store no of occurence.
    while ((N - i) >= (M - j))
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            cnt++;
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return cnt;
}

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(string &pat, int M, vector<int> &lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0)
            {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int main()
{
    string str = "MAGIC";
    string input[] = {"BBABBM", "CBMBBA", "IBABBG",
                      "GOZBBI", "ABBBBC", "MCIGAM"};
    int n = ARRAY_SIZE(input);
    int m = input[0].size();
    int ans = 0;
    // row wise
    for (int i = 0; i < n; i++)
    {
        string text = input[i];
        // left to right match
        ans += KMPSearch(str, text);
        // right to left match
        reverse(text.begin(), text.end());
        ans += KMPSearch(str, text);
    }

    // column wise;
    for (int i = 0; i < m; i++)
    {
        string text;
        for (int j = 0; j < n; j++)
        {
            text.push_back(input[j][i]);
        }
        // top to down;
        ans += KMPSearch(str, text);
        // down to top;
        reverse(text.begin(), text.end());
        ans += KMPSearch(str, text);
    }

    cout << "Count : " << ans << endl;
    return 0;
}
