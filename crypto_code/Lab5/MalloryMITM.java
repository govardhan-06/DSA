import java.io.*;
import java.net.*;
import java.util.Scanner;

public class MalloryMITM {

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
        for (String part : cipherText.split(",")) {
            if (!part.trim().isEmpty()) {
                plainText.append((char) (Integer.parseInt(part.trim()) ^ key));
            }
        }
        return plainText.toString();
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
        System.out.print("Enter Mallory's fake private key for Alice (m1): ");
        long m1 = sc.nextLong();
        System.out.print("Enter Mallory's fake private key for Bob (m2): ");
        long m2 = sc.nextLong();
        
        ServerSocket serverSocket = new ServerSocket(7500);
        System.out.println("\nMallory (MITM) is intercepting on port 7500...");
        Socket aliceSocket = serverSocket.accept();
        System.out.println("Alice connected to Mallory!");

        Socket bobSocket = new Socket("localhost", 8000);
        System.out.println("Mallory connected to Bob!\n");

        BufferedReader fromAlice = new BufferedReader(new InputStreamReader(aliceSocket.getInputStream()));
        PrintWriter toAlice = new PrintWriter(aliceSocket.getOutputStream(), true);

        BufferedReader fromBob = new BufferedReader(new InputStreamReader(bobSocket.getInputStream()));
        PrintWriter toBob = new PrintWriter(bobSocket.getOutputStream(), true);

        // --- KEY EXCHANGE INTERCEPTION ---
        long aliceA = Long.parseLong(fromAlice.readLine());
        System.out.println("[!] Intercepted Alice's real Public Key: " + aliceA);

        long fakeA = modPow(g, m2, p);
        System.out.println("[!] Generating FAKE Public Key for Bob: FakeA = (g^m2) mod p");
        System.out.println("    Computation: FakeA = (" + g + "^" + m2 + ") mod " + p + " = " + fakeA);
        toBob.println(fakeA);

        long bobB = Long.parseLong(fromBob.readLine());
        System.out.println("[!] Intercepted Bob's real Public Key: " + bobB);

        long fakeB = modPow(g, m1, p);
        System.out.println("[!] Generating FAKE Public Key for Alice: FakeB = (g^m1) mod p");
        System.out.println("    Computation: FakeB = (" + g + "^" + m1 + ") mod " + p + " = " + fakeB);
        toAlice.println(fakeB);

        // --- CALCULATE SEPARATE SHARED KEYS ---
        long keyWithAlice = modPow(aliceA, m1, p);
        System.out.println("\n[*] Calculating Shared Key with Alice: KeyA = (AliceA^m1) mod p");
        System.out.println("    Computation: KeyA = (" + aliceA + "^" + m1 + ") mod " + p + " = " + keyWithAlice);

        long keyWithBob = modPow(bobB, m2, p);
        System.out.println("[*] Calculating Shared Key with Bob: KeyB = (BobB^m2) mod p");
        System.out.println("    Computation: KeyB = (" + bobB + "^" + m2 + ") mod " + p + " = " + keyWithBob);

        // --- MESSAGE INTERCEPTION & ALTERATION ---
        String encryptedFromAlice = fromAlice.readLine();
        String originalMsg = decrypt(encryptedFromAlice, keyWithAlice);
        System.out.println("\n[!] Intercepted & Decrypted Msg from Alice: " + originalMsg);

        String maliciousMsg = originalMsg.replace("100", "9999");
        System.out.println("[!] Altered Msg to: " + maliciousMsg);

        String encryptedForBob = encrypt(maliciousMsg, keyWithBob);
        toBob.println(encryptedForBob);
        System.out.println("[!] Sent altered, re-encrypted message to Bob using KeyB (" + keyWithBob + ").");

        aliceSocket.close(); bobSocket.close(); serverSocket.close();
    }
}