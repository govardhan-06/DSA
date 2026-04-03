import java.io.*;
import java.net.*;
import java.util.Scanner;

public class HMACClient {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        Socket socket = new Socket("localhost", 8100);
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

        // Pre-shared secret key between client and server
        String sharedKey = "NetworkSecurityLabExamKey";

        System.out.println("--- HMAC-SHA512 Client ---");
        System.out.print("Enter message to authenticate: ");
        String message = sc.nextLine();

        System.out.println("\n--- Generating MAC ---");
        System.out.println("Using Shared Key: " + sharedKey);
        
        // Calculate MAC
        String mac = HMACCore.calculateHMAC(sharedKey, message);
        System.out.println("\nFinal Generated MAC: \n" + mac);

        // Send Message and MAC to Server
        out.println(message);
        out.println(mac);
        System.out.println("\nMessage and MAC sent to Server securely.");

        socket.close();
        sc.close();
    }
}