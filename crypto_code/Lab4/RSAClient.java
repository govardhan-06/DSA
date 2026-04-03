import java.io.*;
import java.net.*;
import java.util.Scanner;

public class RSAClient {

    // Modular Exponentiation
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

        Socket socket = new Socket("localhost", 8080);

        BufferedReader in = new BufferedReader(
                new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        Scanner sc = new Scanner(System.in);

        // Receive public key
        long e = Long.parseLong(in.readLine());
        long n = Long.parseLong(in.readLine());

        System.out.println("Connected to Server");
        System.out.println("Public Key received: (" + e + ", " + n + ")");

        // Input message
        System.out.print("\nEnter message: ");
        String message = sc.nextLine();

        StringBuilder encrypted = new StringBuilder();

        System.out.println("\n===== ENCRYPTION =====");

        for (char ch : message.toCharArray()) {
            long m = (long) ch;

            long c = modPow(m, e, n);

            System.out.println("'" + ch + "' -> " + c);

            encrypted.append(c).append(",");
        }

        // Send encrypted message
        out.println(encrypted.toString());

        System.out.println("\nEncrypted message sent!");

        socket.close();
        sc.close();
    }
}