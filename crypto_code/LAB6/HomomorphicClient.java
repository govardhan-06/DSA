import java.io.*;
import java.net.*;
import java.util.Scanner;

public class HomomorphicClient {

    public static long modPow(long base, long exp, long mod) {
        long result = 1;
        base %= mod;

        while (exp > 0) {
            if (exp % 2 == 1)
                result = (result * base) % mod;

            exp /= 2;
            base = (base * base) % mod;
        }
        return result;
    }

    public static void main(String[] args) throws Exception {

        Socket s = new Socket("localhost", 8070);

        BufferedReader in = new BufferedReader(
                new InputStreamReader(s.getInputStream()));
        PrintWriter out = new PrintWriter(s.getOutputStream(), true);

        Scanner sc = new Scanner(System.in);

        // Receive public key
        long e = Long.parseLong(in.readLine());
        long n = Long.parseLong(in.readLine());

        System.out.println("Received Public Key (e,n): (" + e + "," + n + ")");

        System.out.print("Enter m1: ");
        long m1 = sc.nextLong();

        System.out.print("Enter m2: ");
        long m2 = sc.nextLong();

        System.out.println("Expected m1*m2 = " + (m1 * m2));

        // Encrypt
        long c1 = modPow(m1, e, n);
        long c2 = modPow(m2, e, n);

        System.out.println("\nC1 = (m1^e) mod n = " + c1);
        System.out.println("C2 = (m2^e) mod n = " + c2);

        // Send to server
        out.println(c1);
        out.println(c2);

        System.out.println("\nCiphertexts sent to server.");

        s.close();
    }
}