import java.io.*;
import java.net.*;
import java.util.Scanner;

public class BobServer {

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

    public static String decrypt(String cipherText, long key) {
        StringBuilder plainText = new StringBuilder();
        String[] parts = cipherText.split(",");
        for (String part : parts) {
            if (!part.trim().isEmpty()) {
                plainText.append((char) (Integer.parseInt(part.trim()) ^ key));
            }
        }
        return plainText.toString();
    }

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        
        // Get parameters from user
        System.out.print("Enter prime number (p): ");
        long p = sc.nextLong();
        System.out.print("Enter generator (g): ");
        long g = sc.nextLong();
        System.out.print("Enter Bob's private key (b): ");
        long b = sc.nextLong();
        
        ServerSocket serverSocket = new ServerSocket(8000);
        System.out.println("\nBob (Server) is waiting on port 8000...");
        
        Socket socket = serverSocket.accept();
        System.out.println("Connection established.");

        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        // 1. Receive Alice's (actually Mallory's) public key
        long receivedA = Long.parseLong(in.readLine());
        System.out.println("\n[1] Received Public Key (supposedly from Alice): " + receivedA);

        // 2. Generate and send Bob's public key
        long B = modPow(g, b, p);
        System.out.println("[2] Generating Public Key B using formula: B = (g^b) mod p");
        System.out.println("    Computation: B = (" + g + "^" + b + ") mod " + p + " = " + B);
        out.println(B);

        // 3. Calculate Shared Secret Key
        long sharedKey = modPow(receivedA, b, p);
        System.out.println("[3] Calculating Shared Secret Key using formula: Key = (A^b) mod p");
        System.out.println("    Computation: Key = (" + receivedA + "^" + b + ") mod " + p + " = " + sharedKey);

        // 4. Receive encrypted message and decrypt
        String encryptedMsg = in.readLine();
        System.out.println("\n[4] Received Encrypted Message: [" + encryptedMsg + "]");
        
        System.out.println("[5] Decrypting message using XOR cipher with Shared Key (" + sharedKey + ")...");
        String decryptedMsg = decrypt(encryptedMsg, sharedKey);
        System.out.println("    Decrypted Message: " + decryptedMsg);

        socket.close();
        serverSocket.close();
    }
}