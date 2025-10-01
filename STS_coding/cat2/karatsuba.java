import java.math.BigInteger;
import java.util.Scanner;

public class SimpleKaratsuba {

    public static BigInteger karatsuba(BigInteger x, BigInteger y) {
        // Base case: single-digit numbers
        if (x.compareTo(BigInteger.TEN) < 0 || y.compareTo(BigInteger.TEN) < 0) {
            return x.multiply(y);
        }

        // Convert numbers to strings for easy splitting
        String X = x.toString();
        String Y = y.toString();
        int n = Math.max(X.length(), Y.length());
        int half = (n + 1) / 2;

        // Split numbers
        BigInteger a = new BigInteger(X.substring(0, X.length() - half));
        BigInteger b = new BigInteger(X.substring(X.length() - half));
        BigInteger c = new BigInteger(Y.substring(0, Y.length() - half));
        BigInteger d = new BigInteger(Y.substring(Y.length() - half));

        // Recursive multiplications
        BigInteger ac = karatsuba(a, c);
        BigInteger bd = karatsuba(b, d);
        BigInteger adbc = karatsuba(a.add(b), c.add(d)).subtract(ac).subtract(bd);

        // Combine results
        BigInteger tenPowHalf = BigInteger.TEN.pow(half);
        return ac.multiply(tenPowHalf.pow(2)).add(adbc.multiply(tenPowHalf)).add(bd);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter first number:");
        BigInteger x = sc.nextBigInteger();
        System.out.println("Enter second number:");
        BigInteger y = sc.nextBigInteger();

        BigInteger product = karatsuba(x, y);
        System.out.println("Product: " + product);
        sc.close();
    }
}
