import java.net.*;
import java.io.*;
import java.util.Scanner;

public class AESServer {
    public static void main(String[] args) throws Exception {

        ServerSocket ss = new ServerSocket(8060);
        System.out.println("AES Server Started on port 8060...");
        System.out.println("Waiting for client connection...\n");

        while (true) {
            Socket s = ss.accept();
            System.out.println("Client connected!");

            BufferedReader in = new BufferedReader(
                    new InputStreamReader(s.getInputStream()));

            String ciphertext = in.readLine();

            if (ciphertext != null) {
                System.out.println("========== RECEIVED FROM CLIENT ==========");
                System.out.println("Received Ciphertext: " + ciphertext);
                System.out.println();

                Scanner sc = new Scanner(System.in);
                System.out.print("Enter 16-character Key for Decryption: ");
                String keyStr = sc.nextLine();
                while (keyStr.length() < 16) keyStr += "0";
                keyStr = keyStr.substring(0, 16);

                System.out.println("\n========== AES-128 DECRYPTION AT SERVER ==========\n");
                String decrypted = AESCore.decrypt(ciphertext, keyStr);

                String decryptedASCII = hexToASCII(decrypted);
                System.out.println("Decrypted Plaintext (Hex): " + decrypted);
                System.out.println("Decrypted Plaintext (ASCII): " + decryptedASCII);
            }

            s.close();
            break; // Close server after one client
        }

        ss.close();
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