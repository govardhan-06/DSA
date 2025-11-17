import java.util.*;

class Prep {

    static void findLongestPalindromicString(String text) {
        int N = text.length();
        if (N == 0)
            return;

        N = 2 * N + 1;               // Transformed string length (# + characters)
        int[] L = new int[N + 1];    // LPS array for transformed string

        L[0] = 0;
        L[1] = 1;

        int C = 1;                   // Center of current palindrome
        int R = 2;                   // Right boundary of current palindrome
        int i, iMirror;

        int maxLPSLength = 0;
        int maxLPSCenterPosition = 0;

        int start = -1, end = -1;
        int diff;

        for (i = 2; i < N; i++) {

            // iMirror = C - (i - C)
            iMirror = 2 * C - i;
            L[i] = 0;
            diff = R - i;

            // If i is inside current palindrome
            if (diff > 0)
                L[i] = Math.min(L[iMirror], diff);

            // Attempt to expand palindrome centered at i
            while ((i + L[i] + 1 < N && i - L[i] > 0) &&
                    (
                        // even positions: always valid for expansion
                        ((i + L[i] + 1) % 2 == 0) ||

                        // odd positions: compare actual characters
                        text.charAt((i + L[i] + 1) / 2) ==
                        text.charAt((i - L[i] - 1) / 2)
                    )
            ) {
                L[i]++;
            }

            // If palindrome centered at i expands beyond R, adjust center
            if (i + L[i] > R) {
                C = i;
                R = i + L[i];
            }

            // Update max LPS
            if (L[i] > maxLPSLength) {
                maxLPSLength = L[i];
                maxLPSCenterPosition = i;
            }
        }

        // Compute start and end indices in original string
        start = (maxLPSCenterPosition - maxLPSLength) / 2;
        end = start + maxLPSLength - 1;

        System.out.println("Longest Palindromic Substring: " + text.substring(start, end + 1));
        System.out.println("Length: " + (end - start + 1));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String text = sc.nextLine();
        findLongestPalindromicString(text);
    }
}
