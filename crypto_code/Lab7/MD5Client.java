import java.io.*;
import java.net.*;
import java.security.MessageDigest;
import java.util.Scanner;

public class MD5Client {
    // Modular function for MD5 as required by lab rubric
    public static String calculateMD5(String input) throws Exception {
        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] digest = md.digest(input.getBytes());
        
        StringBuilder hexString = new StringBuilder();
        for (byte b : digest) {
            hexString.append(String.format("%02x", b));
        }
        return hexString.toString();
    }

    private static String toHex(byte[] bytes) {
        StringBuilder hex = new StringBuilder();
        for (byte b : bytes) {
            hex.append(String.format("%02x", b));
        }
        return hex.toString();
    }

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in);
             Socket socket = new Socket("localhost", 7000);
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {
             
            System.out.print("Enter message to hash with MD5: ");
            String message = sc.nextLine();
            
            System.out.println("Step 1: Message = " + message);
            byte[] messageBytes = message.getBytes();
            System.out.println("Step 2: Message bytes (hex) = " + toHex(messageBytes));
            System.out.println("Step 3: Computing MD5 digest...");
            String md5Hash = calculateMD5(message);
            
            System.out.println("Step 4: Generated MD5 Hash = " + md5Hash);
            
            // Send both message and hash to server
            out.println(message);
            out.println(md5Hash);
            System.out.println("Step 5: Message and hash sent to server successfully.");
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}