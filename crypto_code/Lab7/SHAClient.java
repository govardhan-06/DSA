import java.io.*; 
import java.net.*; 
import java.util.*; 

public class SHAClient { 
    public static void main(String[] args) { 
        try { 
            Scanner sc = new Scanner(System.in); 
            System.out.print("Enter message: "); 
            String message = sc.nextLine(); 
 
            byte[] bytes = message.getBytes(); 
            long messageLength = bytes.length * 8; 
            StringBuilder binary = new StringBuilder(); 
 
            // 1. Convert message to binary
            for (byte b : bytes) { 
                binary.append(String.format("%8s", Integer.toBinaryString(b & 0xFF)).replace(' ', '0')); 
            } 
 
            // 2. Append '1' bit
            binary.append("1"); 
 
            // 3. Pad with '0's until length is congruent to 896 mod 1024
            while ((binary.length() % 1024) != 896) { 
                binary.append("0"); 
            } 
 
            // 4. Append 128-bit message length
            String lengthBinary = String.format("%128s", Long.toBinaryString(messageLength)).replace(' ', '0'); 
            binary.append(lengthBinary); 
 
            String block = binary.substring(0, 1024); 
            String[] words = new String[16]; 
 
            // 5. Extract first 16 words (64 bits each)
            for (int i = 0; i < 16; i++) { 
                words[i] = block.substring(i * 64, (i + 1) * 64); 
            } 
 
            // 6. Send to server
            Socket socket = new Socket("localhost", 5000); 
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true); 
 
            for (int i = 0; i < 16; i++) { 
                out.println(words[i]); 
            } 
            
            System.out.println("1024-bit block successfully preprocessed and sent to server.");
            socket.close(); 
            sc.close();
 
        } catch (Exception e) { 
            e.printStackTrace(); 
        } 
    } 
}