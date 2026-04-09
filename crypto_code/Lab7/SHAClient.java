import java.io.*; 
import java.net.*; 
import java.security.MessageDigest;
import java.util.Scanner; 

public class SHAClient { 
    public static String calculateSHA512(String input) throws Exception { 
        MessageDigest md = MessageDigest.getInstance("SHA-512"); 
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
        try { 
            Scanner sc = new Scanner(System.in); 
            System.out.print("Enter message to hash with SHA-512: "); 
            String message = sc.nextLine(); 
            byte[] messageBytes = message.getBytes();
            System.out.println("Step 1: Message = " + message);
            System.out.println("Step 2: Message bytes (hex) = " + toHex(messageBytes));
            
            // SHA-512 Preprocessing (Optional)
            System.out.println("\n=== SHA-512 PREPROCESSING ===");
            long messageLength = messageBytes.length * 8;
            StringBuilder binary = new StringBuilder();
            
            // Convert message to binary
            for (byte b : messageBytes) {
                binary.append(String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0'));
            }
            System.out.println("Step 3a: Message in binary (first 64 bits): " + (binary.length() >= 64 ? binary.substring(0, 64) : binary.toString()));
            
            // Append '1' bit
            binary.append("1");
            System.out.println("Step 3b: After appending '1' bit: length = " + binary.length());
            
            // Pad with '0's until length is congruent to 896 mod 1024
            while ((binary.length() % 1024) != 896) {
                binary.append("0");
            }
            System.out.println("Step 3c: After padding: length = " + binary.length());
            
            // Append 128-bit message length
            String lengthBinary = String.format("%128s", Long.toBinaryString(messageLength)).replace(' ', '0');
            binary.append(lengthBinary);
            System.out.println("Step 3d: After appending message length: total length = " + binary.length());
            
            // Extract first 16 words (64 bits each)
            String block = binary.substring(0, 1024);
            String[] words = new String[16];
            System.out.println("\nStep 3e: Message Schedule Words (W0-W15):");
            for (int i = 0; i < 16; i++) {
                words[i] = block.substring(i * 64, (i + 1) * 64);
                System.out.println("  W" + i + " = " + words[i]);
            }
            
            System.out.println("\nStep 4: Computing SHA-512 digest...");
            String sha512Hash = calculateSHA512(message); 

            System.out.println("Step 5: Generated SHA-512 Hash = " + sha512Hash); 

            Socket socket = new Socket("localhost", 5000); 
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true); 
 
            out.println(message); 
            out.println(sha512Hash); 

            System.out.println("Step 6: Message and SHA-512 hash sent to server successfully."); 

            socket.close(); 
            sc.close();
 
        } catch (Exception e) { 
            e.printStackTrace(); 
        } 
    } 
}