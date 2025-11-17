import java.util.*;

public class NaturalSortEasy {

    public static void main(String[] args) {
        List<String> list = Arrays.asList(
                "file1.txt", "file10.txt", "file2.txt", "file20.txt", "file3.txt"
        );

        list.sort(NaturalSortEasy::naturalCompare);

        for (String s : list) {
            System.out.println(s);
        }
    }

    public static int naturalCompare(String a, String b) {
        int i = 0, j = 0;
        int n1 = a.length(), n2 = b.length();

        while (i < n1 && j < n2) {
            char c1 = a.charAt(i);
            char c2 = b.charAt(j);

            // If both characters are digits → compare numbers
            if (Character.isDigit(c1) && Character.isDigit(c2)) {
                int num1 = 0;
                while (i < n1 && Character.isDigit(a.charAt(i))) {
                    num1 = num1 * 10 + (a.charAt(i) - '0');
                    i++;
                }

                int num2 = 0;
                while (j < n2 && Character.isDigit(b.charAt(j))) {
                    num2 = num2 * 10 + (b.charAt(j) - '0');
                    j++;
                }

                if (num1 != num2) return Integer.compare(num1, num2);
            }
            else {
                // Compare characters normally
                if (c1 != c2) return Character.compare(c1, c2);
                i++;
                j++;
            }
        }

        // If one string ended earlier
        return Integer.compare(n1, n2);
    }
}
