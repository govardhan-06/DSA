import java.io.*;
import java.net.*;
import java.util.Scanner;

public class RSAServer {

    // 1. GCD using Euclidean Algorithm
    public static long gcd(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // 2. Modular Inverse using Extended Euclidean Algorithm
    public static long modInverse(long e, long phi) {
        long m0 = phi, t, q;
        long x0 = 0, x1 = 1;

        if (phi == 1) return 0;

        while (e > 1) {
            q = e / phi;

            t = phi;
            phi = e % phi;
            e = t;

            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }

        if (x1 < 0) x1 += m0;

        return x1;
    }

    // 3. Fast Modular Exponentiation
    public static long modPow(long base, long exp, long mod) {
        long result = 1;
        base = base % mod;

        while (exp > 0) {
            if ((exp & 1) == 1)
                result = (result * base) % mod;

            exp = exp >> 1;
            base = (base * base) % mod;
        }

        return result;
    }

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        System.out.println("===== RSA KEY GENERATION =====");
        
        System.out.print("Enter first prime number (p): ");
        long p = sc.nextLong();
        System.out.print("Enter second prime number (q): ");
        long q = sc.nextLong();

        System.out.println("\np = " + p + ", q = " + q);

        long n = p * q;
        long phi = (p - 1) * (q - 1);

        System.out.println("n = p * q = " + n);
        System.out.println("phi(n) = " + phi);

        // Find e
        long e = 2;
        while (e < phi) {
            if (gcd(e, phi) == 1)
                break;
            e++;
        }

        System.out.println("Public exponent e = " + e);

        // Find d
        long d = modInverse(e, phi);
        System.out.println("Private exponent d = " + d);

        System.out.println("\nPublic Key: (" + e + ", " + n + ")");
        System.out.println("Private Key: (" + d + ", " + n + ")");

        // Socket setup
        ServerSocket server = new ServerSocket(8080);
        System.out.println("\nServer started on port 8080...");

        Socket socket = server.accept();
        System.out.println("Client connected!");

        BufferedReader in = new BufferedReader(
                new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        // Send public key
        out.println(e);
        out.println(n);

        // Receive encrypted message
        String encrypted = in.readLine();
        System.out.println("\nReceived Cipher Text: " + encrypted);

        String[] parts = encrypted.split(",");
        StringBuilder decrypted = new StringBuilder();

        System.out.println("\n===== DECRYPTION =====");

        for (String part : parts) {
            if (!part.isEmpty()) {
                long c = Long.parseLong(part.trim());

                long m = modPow(c, d, n);

                System.out.println("C = " + c + " -> M = " + m + " ('" + (char) m + "')");

                decrypted.append((char) m);
            }
        }

        System.out.println("\nFinal Decrypted Message: " + decrypted.toString());

        socket.close();
        server.close();
        sc.close();
    }
}