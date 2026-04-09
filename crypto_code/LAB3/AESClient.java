import java.net.*;
import java.io.*;
import java.util.Scanner;

public class AESClient {
    public static void main(String[] args) throws Exception {

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Plaintext (max 16 characters): ");
        String pt = sc.nextLine();

        // Pad or truncate to 16 characters
        while (pt.length() < 16) pt += "X";
        pt = pt.substring(0, 16);

        System.out.print("Enter 16-character Key: ");
        String keyStr = sc.nextLine();
        while (keyStr.length() < 16) keyStr += "0";
        keyStr = keyStr.substring(0, 16);

        System.out.println("\n========== AES-128 ENCRYPTION ==========\n");
        System.out.println("Plaintext: " + pt);
        System.out.println("Key: " + keyStr);
        System.out.println();

        // Perform full encryption with round-by-round output
        String ciphertext = AESCore.encrypt(pt, keyStr);

        System.out.println("========== AES-128 DECRYPTION ==========\n");
        System.out.println("Ciphertext to Decrypt: " + ciphertext);
        System.out.println();

        // Perform full decryption with round-by-round output
        String decrypted = AESCore.decrypt(ciphertext, keyStr);

        System.out.println("========== VERIFICATION ==========");
        System.out.println("Original Plaintext: " + pt);
        System.out.println("Decrypted Result:   " + decrypted);
        
        // Convert hex to ASCII for better readability
        String decryptedASCII = hexToASCII(decrypted);
        System.out.println("Decrypted (ASCII): " + decryptedASCII);
        System.out.println("Match: " + pt.equals(decryptedASCII));

        // Send ciphertext to server
        try {
            Socket s = new Socket("localhost", 8060);
            PrintWriter out = new PrintWriter(s.getOutputStream(), true);
            System.out.println("\n========== SENDING TO SERVER ==========");
            out.println(ciphertext);
            System.out.println("Ciphertext sent to server: " + ciphertext);
            s.close();
        } catch (Exception e) {
            System.out.println("Server not available - skipping network transmission");
        }

        sc.close();
    }

    private static String hexToASCII(String hex) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < hex.length(); i += 2) {
            String hexByte = hex.substring(i, i + 2);
            int charCode = Integer.parseInt(hexByte, 16);
            result.append((char) charCode);
        }
        return result.toString();
    }
}