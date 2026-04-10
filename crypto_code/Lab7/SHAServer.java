import java.io.*; 
import java.net.*; 
import java.security.MessageDigest;

public class SHAServer { 
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
            ServerSocket serverSocket = new ServerSocket(5000); 
            System.out.println("SHA-512 Server waiting for client on port 5000..."); 
 
            Socket socket = serverSocket.accept(); 
            System.out.println("Client connected!"); 
 
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream())); 
 
            String message = in.readLine(); 
            String receivedHash = in.readLine(); 

            System.out.println("\nReceived Message: " + message); 
            System.out.println("Received SHA-512 Hash: " + receivedHash); 
            
            // SHA-512 Preprocessing
            // System.out.println("\n=== SHA-512 PREPROCESSING ===");
            // byte[] messageBytes = message.getBytes();
            // long messageLength = messageBytes.length * 8;
            // StringBuilder binary = new StringBuilder();
            
            // // Convert message to binary
            // for (byte b : messageBytes) {
            //     binary.append(String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0'));
            // }
            
            // // Append '1' bit and pad
            // binary.append("1");
            // while ((binary.length() % 1024) != 896) {
            //     binary.append("0");
            // }
            
            // // Append 128-bit message length
            // String lengthBinary = String.format("%128s", Long.toBinaryString(messageLength)).replace(' ', '0');
            // binary.append(lengthBinary);
            
            // // Extract first 16 words (64 bits each)
            // String block = binary.substring(0, 1024);
            // System.out.println("Step 1: Message Schedule Words (W0-W15):");
            // for (int i = 0; i < 16; i++) {
            //     String word = block.substring(i * 64, (i + 1) * 64);
            //     System.out.println("  W" + i + " = " + word);
            // }
            
            System.out.println("\nStep 2: Received message bytes (hex) = " + toHex(message.getBytes())); 
            System.out.println("Step 3: Recomputing SHA-512 digest on server..."); 

            String calculatedHash = calculateSHA512(message); 
            System.out.println("Step 4: Calculated SHA-512 Hash = " + calculatedHash); 
 
            System.out.println("Step 5: Comparing client hash with server hash..."); 
            if (calculatedHash.equals(receivedHash)) { 
                System.out.println("\nHash Verification SUCCESS. Message is authentic and unmodified."); 
            } else { 
                System.out.println("\nHash Mismatch. Message has been tampered with!"); 
            } 
 
            socket.close(); 
            serverSocket.close(); 
 
        } catch (Exception e) { 
            e.printStackTrace(); 
        } 
    }

    public static String calculateHash(String message) throws Exception{
        MessageDigest md=new MessageDigest.getInstance("SHA-512");
        byte[] digest=md.digest(message.getBytes());
        StringBuilder sb=new StringBuilder();
        for(byte b:digest){
            sb.append(String.format("%02x",b));
        }
        return sb.toString();
    } 
}