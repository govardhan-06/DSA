import java.io.*;
import java.net.*;
import java.util.Scanner;

public class AliceClient {

    public static long modPow(long base, long exp, long mod) {
        long res = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % mod;
            exp = exp >> 1;
            base = (base * base) % mod;
        }
        return res;
    }

    public static String encrypt(String msg, long key) {
        StringBuilder cipherText = new StringBuilder();
        for (char c : msg.toCharArray()) {
            cipherText.append(c ^ key).append(",");
        }
        return cipherText.toString();
    }

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        
        // Get parameters from user
        System.out.print("Enter prime number (p): ");
        long p = sc.nextLong();
        System.out.print("Enter generator (g): ");
        long g = sc.nextLong();
        System.out.print("Enter Alice's private key (a): ");
        long a = sc.nextLong();
        System.out.print("Enter message to send: ");
        sc.nextLine(); // consume newline
        String message = sc.nextLine();
        
        Socket socket = new Socket("localhost", 7500); 
        
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        // 1. Generate and send Alice's public key
        long A = modPow(g, a, p);
        System.out.println("[1] Generating Public Key A using formula: A = (g^a) mod p");
        System.out.println("    Computation: A = (" + g + "^" + a + ") mod " + p + " = " + A);
        out.println(A);

        // 2. Receive Bob's (actually Mallory's) public key
        long receivedB = Long.parseLong(in.readLine());
        System.out.println("\n[2] Received Public Key (supposedly from Bob): " + receivedB);

        // 3. Calculate Shared Secret Key
        long sharedKey = modPow(receivedB, a, p);
        System.out.println("[3] Calculating Shared Secret Key using formula: Key = (B^a) mod p");
        System.out.println("    Computation: Key = (" + receivedB + "^" + a + ") mod " + p + " = " + sharedKey);

        // 4. Encrypt and send message
        System.out.println("\n[4] Original Message: " + message);
        
        System.out.println("[5] Encrypting message using XOR cipher with Shared Key (" + sharedKey + ")...");
        String encryptedMsg = encry-pt(message, sharedKey);
        System.out.println("    Sending Encrypted Message: [" + encryptedMsg + "]");
        out.println(encryptedMsg);

        socket.close();
        sc.close();
    }
}