import java.io.*;
import java.net.*;

public class HMACServer {
    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket = new ServerSocket(8100);
        System.out.println("HMAC Server waiting on port 8100...");

        Socket socket = serverSocket.accept();
        System.out.println("Client connected!\n");

        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        // Pre-shared secret key (must match the client)
        String sharedKey = "NetworkSecurityLabExamKey";

        // Receive Data
        String receivedMessage = in.readLine();
        String receivedMAC = in.readLine();

        System.out.println("--- DATA RECEIVED ---");
        System.out.println("Message: " + receivedMessage);
        System.out.println("Attached MAC: \n" + receivedMAC);

        System.out.println("\n--- VERIFICATION PROCESS ---");
        System.out.println("Computing Expected MAC using Shared Secret Key...");
        
        // Server independently calculates the MAC using the same shared key
        String expectedMAC = HMACCore.calculateHMAC(sharedKey, receivedMessage);

        System.out.println("\nExpected MAC: \n" + expectedMAC);

        // Compare the MACs
        System.out.println("\n--- VERIFICATION RESULT ---");
        if (expectedMAC.equals(receivedMAC)) {
            System.out.println("[SUCCESS] MAC matched! The message is Authentic and retains Integrity.");
        } else {
            System.out.println("[FAILED] MAC mismatch! The message was tampered with or sent by an imposter.");
        }

        socket.close();
        serverSocket.close();
    }
}