import java.util.Scanner;

public class Booth {

    public int multiply(int n1, int n2) {
        int m = n1;  // multiplicand
        int r = n2;  // multiplier
        int x = Math.max(Integer.toBinaryString(Math.abs(n1)).length(),
                         Integer.toBinaryString(Math.abs(n2)).length());

        int count = x;  // number of bits needed
        int A = m << (x + 1);
        int S = (-m) << (x + 1);
        int P = r << 1; // leave one extra bit Q(-1) = 0

        while (count > 0) {
            int lastTwo = P & 3; // check last two bits (Q0 and Q-1)
            if (lastTwo == 1) {       // 01 → add A
                P += A;
            } else if (lastTwo == 2) { // 10 → add S
                P += S;
            }
            P >>= 1; // arithmetic right shift
            count--;
        }
        return P >> 1; // final result (discard extra bit)
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        Booth b = new Booth();
        System.out.println("Enter two integer numbers -");
        int n1 = scan.nextInt();
        int n2 = scan.nextInt();
        int result = b.multiply(n1, n2);
        System.out.println("\nResult : " + n1 + " * " + n2 + " = " + result);
        scan.close();
    }
}
