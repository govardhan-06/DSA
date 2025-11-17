import java.util.*;

public class CombinationExample {

    static int fact(int number) {
        int f = 1;
        int j = 1;
        while (j <= number) {
            f = f * j;
            j++;
        }
        return f;
    }

    public static void main(String args[]) {

        List<Integer> numbers = new ArrayList<>();
        numbers.add(9);
        numbers.add(12);
        numbers.add(19);
        numbers.add(61);
        numbers.add(19);

        int n = numbers.size();  // n = 5
        int r = 2;

        int result = fact(n) / (fact(r) * fact(n - r));

        System.out.println("The combination value for the numbers list is: " + result);
    }
}
