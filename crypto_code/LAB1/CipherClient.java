import java.io.*;
import java.net.*;
import java.util.Scanner;

public class CipherClient {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        Socket socket = new Socket("localhost", 8090);
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        System.out.println("Select Classical Cipher to test:");
        System.out.println("1. Caesar Cipher");
        System.out.println("2. Vigenere Cipher");
        System.out.println("3. Playfair Cipher");
        System.out.print("Choice: ");
        int choice = sc.nextInt();
        sc.nextLine(); // consume newline

        System.out.print("Enter Plaintext: ");
        String plainText = sc.nextLine();
        
        String key = "";
        String cipherText = "";

        if (choice == 1) {
            System.out.print("Enter Caesar Shift (Integer): ");
            key = sc.nextLine();
            System.out.println("\n--- ENCRYPTING ---");
            cipherText = ClassicalCiphers.caesarEncrypt(plainText, Integer.parseInt(key));
        } else if (choice == 2) {
            System.out.print("Enter Vigenere Keyword: ");
            key = sc.nextLine();
            System.out.println("\n--- ENCRYPTING ---");
            cipherText = ClassicalCiphers.vigenereEncrypt(plainText, key);
        } else if (choice == 3) {
            System.out.print("Enter Playfair Keyword: ");
            key = sc.nextLine();
            System.out.println("\n--- ENCRYPTING ---");
            cipherText = ClassicalCiphers.playfairProcess(plainText, key, true);
        }

        System.out.println("\nFinal Ciphertext: " + cipherText);

        // Send to Server: [Choice] -> [Key] -> [CipherText]
        out.println(choice);
        out.println(key);
        out.println(cipherText);
        System.out.println("Data sent to server for decryption.");

        socket.close();
        sc.close();
    }
}