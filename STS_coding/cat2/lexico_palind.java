import java.util.Scanner;

public class PalindromeBuilder {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter a string:");
        String s = sc.nextLine().toLowerCase(); // convert to lowercase

        if (!canMakePalindrome(s)) {
            System.out.println("No palindromic string can be formed.");
        } else {
            System.out.println("Palindromic string: " + buildPalindrome(s));
        }

        sc.close();
    }

    // Check if palindrome can be formed
    public static boolean canMakePalindrome(String s) {
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            if (c >= 'a' && c <= 'z')
                freq[c - 'a']++;
        }

        int oddCount = 0;
        for (int f : freq) {
            if (f % 2 != 0) oddCount++;
        }

        return (s.length() % 2 == 0) ? (oddCount == 0) : (oddCount == 1);
    }

    // Build a palindrome using the character frequencies
    public static String buildPalindrome(String s) {
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            if (c >= 'a' && c <= 'z')
                freq[c - 'a']++;
        }

        StringBuilder firstHalf = new StringBuilder();
        StringBuilder middle = new StringBuilder();

        // Handle odd-count character
        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 != 0) {
                middle.append((char) (i + 'a'));
                freq[i]--; // reduce to make count even
            }
        }

        // Build first half and its reverse
        StringBuilder secondHalf = new StringBuilder();
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < freq[i] / 2; j++) {
                char ch = (char) (i + 'a');
                firstHalf.append(ch);
                secondHalf.insert(0, ch); // prepend to reverse
            }
        }

        return firstHalf.toString() + middle.toString() + secondHalf.toString();
    }
}
