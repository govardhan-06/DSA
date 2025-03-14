#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define d 256
#define q 101

// Rabin-Karp algorithm
void RabinKarp(string &T, string &P)
{
    int n = T.length();
    int m = P.length();
    int h = 1;        // Hash value for pattern shifting
    int p = 0, t = 0; // Hash values for the pattern and the text

    // Compute h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++)
    {
        h = (h * d) % q;
    }

    // Compute initial hash values for pattern and text's first window
    for (int i = 0; i < m; i++)
    {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }

    // Slide the pattern over text
    for (int s = 0; s <= n - m; s++)
    {
        // If hash values match, check characters one by one
        if (p == t)
        {
            bool match = true;
            // Check characters one by one
            for (int i = 0; i < m; i++)
            {
                if (P[i] != T[s + i])
                {
                    match = false;
                    break;
                }
            }
            if (match)
            {
                cout << "Pattern occurs with shift " << s << endl;
            }
        }

        // Compute hash for the next window
        if (s < n - m)
        {
            //   d * <-----t------> + T[i] % q : formula like the one used in the loop above
            t = (d * (t - T[s] * h) + T[s + m]) % q;

            // Ensure t is positive
            if (t < 0)
            {
                t += q;
            }
        }
    }
}

int main()
{
    string T = "ABABDABACDABABCABAB";
    string P = "ABABCABAB";
    RabinKarp(T, P);
    return 0;
}