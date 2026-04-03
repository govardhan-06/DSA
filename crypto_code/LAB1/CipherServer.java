import java.io.*;
import java.net.*;

public class CipherServer {
    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket = new ServerSocket(8090);
        System.out.println("Cipher Server listening on port 8090...");

        Socket socket = serverSocket.accept();
        System.out.println("Client connected!\n");

        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        
        int choice = Integer.parseInt(in.readLine());
        String key = in.readLine();
        String cipherText = in.readLine();

        System.out.println("--- RECEIVED DATA ---");
        System.out.println("Ciphertext: " + cipherText);
        System.out.println("Key: " + key + "\n");
        System.out.println("--- DECRYPTING ---");

        String decryptedText = "";

        if (choice == 1) {
            System.out.println("Algorithm: Caesar Cipher");
            decryptedText = ClassicalCiphers.caesarDecrypt(cipherText, Integer.parseInt(key));
        } else if (choice == 2) {
            System.out.println("Algorithm: Vigenere Cipher");
            decryptedText = ClassicalCiphers.vigenereDecrypt(cipherText, key);
        } else if (choice == 3) {
            System.out.println("Algorithm: Playfair Cipher");
            // False flag indicates decryption
            decryptedText = ClassicalCiphers.playfairProcess(cipherText, key, false); 
        }

        System.out.println("\nRecovered Plaintext: " + decryptedText);

        socket.close();
        serverSocket.close();
    }
}