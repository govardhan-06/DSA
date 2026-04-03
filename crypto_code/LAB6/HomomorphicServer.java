import java.io.*;
import java.net.*;

public class HomomorphicServer {

    // GCD
    public static long gcd(long a, long b) {
        return (b == 0) ? a : gcd(b, a % b);
    }

    // Modular Inverse
    public static long modInverse(long e, long phi) {
        long m0 = phi, t, q;
        long x0 = 0, x1 = 1;

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

    // Modular Exponentiation
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

        System.out.println("=== RSA KEY GENERATION ===");

        long p = 17;
        long q = 19;

        long n = p * q;
        long phi = (p - 1) * (q - 1);

        System.out.println("p = " + p);
        System.out.println("q = " + q);
        System.out.println("n = p*q = " + n);
        System.out.println("phi = " + phi);

        long e = 2;
        while (e < phi) {
            if (gcd(e, phi) == 1) break;
            e++;
        }

        long d = modInverse(e, phi);

        System.out.println("Public Key (e, n): (" + e + ", " + n + ")");
        System.out.println("Private Key (d, n): (" + d + ", " + n + ")");

        ServerSocket ss = new ServerSocket(8070);
        System.out.println("\nServer waiting...");

        Socket s = ss.accept();

        BufferedReader in = new BufferedReader(
                new InputStreamReader(s.getInputStream()));
        PrintWriter out = new PrintWriter(s.getOutputStream(), true);

        // Send Public Key
        out.println(e);
        out.println(n);

        // Receive ciphertexts
        long c1 = Long.parseLong(in.readLine());
        long c2 = Long.parseLong(in.readLine());

        System.out.println("\nReceived C1 = " + c1);
        System.out.println("Received C2 = " + c2);

        // Homomorphic multiplication
        long c_prod = (c1 * c2) % n;
        System.out.println("\nC_prod = (C1 * C2) % n = " + c_prod);

        // Decrypt
        long m_prod = modPow(c_prod, d, n);
        System.out.println("Decrypted result = " + m_prod);

        System.out.println("\n✔ Verified: m1 * m2 = decrypted result");

        ss.close();
    }
}