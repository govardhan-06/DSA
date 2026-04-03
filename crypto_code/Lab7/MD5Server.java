import java.io.*;
import java.net.*;
import java.security.MessageDigest;

public class MD5Server {
    
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
        try (ServerSocket serverSocket = new ServerSocket(7000)) {
            System.out.println("MD5 Server waiting for client on port 7000...");
            
            Socket socket = serverSocket.accept();
            System.out.println("Client connected!");
            
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String message = in.readLine();
            String receivedHash = in.readLine();
            
            System.out.println("\nReceived Message from Client: " + message);
            System.out.println("Received MD5 Hash: " + receivedHash);
            
            // Calculate MD5 of received message
            String calculatedHash = calculateMD5(message);
            System.out.println("Calculated MD5 Hash: " + calculatedHash);
            
            // Compare hashes
            if (calculatedHash.equals(receivedHash)) {
                System.out.println("\n✓ Hash Verification SUCCESS. Message is Authentic and Unmodified.");
            } else {
                System.out.println("\n✗ Hash Mismatch. Message has been Tampered!");
            }
            
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}