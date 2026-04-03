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

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in);
             Socket socket = new Socket("localhost", 7000);
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {
             
            System.out.print("Enter message to hash with MD5: ");
            String message = sc.nextLine();
            
            System.out.println("Calculating intermediate hash...");
            String md5Hash = calculateMD5(message);
            
            System.out.println("Generated MD5 Hash: " + md5Hash);
            
            // Send both message and hash to server
            out.println(message);
            out.println(md5Hash);
            System.out.println("Message and hash sent to server successfully.");
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}