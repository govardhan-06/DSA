import java.util.*;

// Get the input string num.
// Generate all strobogrammatic numbers of the same length using your strobo(num.length()).
// Filter out numbers that start with '0' (invalid for >1 digit).
// Compare each candidate with num, and pick the smallest one that is greater.
// If none found, generate strobogrammatic numbers of length num.length()+1 (e.g., 99 → 101).

class StroboLenN {
    public static List<String> strobo(int n) {
        return helper(n, n);
    }

    public static List<String> helper(int n, int totalLength) {
        if (n == 0) return new ArrayList<>(Arrays.asList(""));
        if (n == 1) return new ArrayList<>(Arrays.asList("0", "1", "8"));

        List<String> list = helper(n - 2, totalLength);
        List<String> result = new ArrayList<>();

        for (String s : list) {
            if (n != totalLength) result.add("0" + s + "0"); // avoid leading zero at outermost
            result.add("1" + s + "1");
            result.add("8" + s + "8");
            result.add("6" + s + "9");
            result.add("9" + s + "6");
        }
        return result;
    }

    public static String nextStrobo(String num) {
        int n = num.length();
        List<String> candidates = strobo(n);

        // Filter valid numbers (no leading 0 if length > 1)
        List<String> valid = new ArrayList<>();
        for (String s : candidates) {
            if (s.length() > 1 && s.startsWith("0")) continue;
            valid.add(s);
        }

        Collections.sort(valid); // sort lexicographically (works since all same length)

        for (String s : valid) {
            if (s.compareTo(num) > 0) return s; // first greater
        }

        // If none found, try with next length
        List<String> nextLen = strobo(n + 1);
        valid.clear();
        for (String s : nextLen) {
            if (s.length() > 1 && s.startsWith("0")) continue;
            valid.add(s);
        }
        Collections.sort(valid);
        return valid.get(0); // smallest strobogrammatic of next length
    }

    public static void main(String[] args) {
        System.out.println(nextStrobo("50")); // 69
        System.out.println(nextStrobo("88")); // 96
        System.out.println(nextStrobo("96")); // 101
    }
}
