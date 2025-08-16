import java.util.*;

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

    public static void main(String[] args) {
        System.out.println(strobo(2)); // prints [11, 69, 88, 96]
    }
}
