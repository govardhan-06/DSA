// C program to check if two given strings are
// rotations of  each other using KMP Algorithm

#include <stdio.h>
#include <string.h>

// Idea:
// The idea is that when a string is concatenated with itself, all possible rotations of the string will naturally appear as
// substrings within this concatenated string. To determine if another string is a rotation of the first,
// we can use KMP Algorithm to check if the second string exists as a substring in the concatenated form of the first string.

int *computeLPSArray(char *pat)
{
    int n = strlen(pat);
    int *lps = (int *)malloc(n * sizeof(int));

    // Length of the previous longest prefix suffix
    int len = 0;

    // lps[0] is always 0
    lps[0] = 0;

    // loop calculates lps[i] for i = 1 to n-1
    int i = 1;
    while (i < n)
    {

        // If the characters match, increment len
        // and extend the matching prefix
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }

        // If there is a mismatch
        else
        {

            // If len is not zero, update len to
            // last known prefix length
            if (len != 0)
            {
                len = lps[len - 1];
            }

            // No prefix matches, set lps[i] = 0
            // and move to the next character
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Function to check if s1 and s2 are rotations of each other
int areRotations(char *s1, char *s2)
{
    char *txt = (char *)malloc(strlen(s1) * 2 + 1);
    strcpy(txt, s1);
    strcat(txt, s1);

    char *pat = s2;

    // search the pattern string s2 in the concatenated string
    int n = strlen(txt);
    int m = strlen(pat);

    // Create lps[] that will hold the longest prefix suffix
    // values for pattern
    int *lps = computeLPSArray(pat);

    int i = 0;
    int j = 0;
    while (i < n)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == m)
        {
            return 1;
        }

        // Mismatch after j matches
        else if (i < n && pat[j] != txt[i])
        {

            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return 0;
}

int main()
{
    char s1[] = "aab";
    char s2[] = "aba";

    printf("%s", (areRotations(s1, s2) ? "true" : "false"));
    return 0;
}
