import java.util.Scanner;

public class LongestSubarrayWithOnesAfterReplacement {

    // Function to find length of longest subarray after replacing at most k zeros
    private static int findMaxConsecutiveOnes(int[] a, int k) {
        int maxOnes = 0;
        int numReplacements = 0;
        int windowStart = 0;

        for (int windowEnd = 0; windowEnd < a.length; windowEnd++) {
            if (a[windowEnd] == 0) {
                numReplacements++;
            }

            // Shrink the window if replacements exceed k
            while (numReplacements > k) {
                if (a[windowStart] == 0) {
                    numReplacements--;
                }
                windowStart++;
            }

            // Update maximum length
            maxOnes = Math.max(maxOnes, windowEnd - windowStart + 1);
        }

        return maxOnes;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the size of the array:");
        int n = sc.nextInt();
        int[] a = new int[n];

        System.out.println("Enter the elements of the array (0s and 1s):");
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
        }

        System.out.println("Enter the maximum number of zeros you can replace (k):");
        int k = sc.nextInt();

        int result = findMaxConsecutiveOnes(a, k);
        System.out.printf("Length of longest contiguous subarray containing only 1s after replacement = %d%n", result);

        sc.close();
    }
}
