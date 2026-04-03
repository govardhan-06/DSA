import java.io.*; 
import java.net.*; 

public class SHAServer { 
    public static void main(String[] args) { 
        try { 
            ServerSocket serverSocket = new ServerSocket(5000); 
            System.out.println("SHA Server waiting for client on port 5000..."); 
 
            Socket socket = serverSocket.accept(); 
            System.out.println("Client connected!"); 
 
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream())); 
 
            System.out.println("\nReceived Message Schedule Words (W0 - W15):\n"); 
 
            for (int i = 0; i < 16; i++) { 
                String word = in.readLine(); 
                System.out.println("W" + i + " : " + word); 
            } 
 
            socket.close(); 
            serverSocket.close(); 
 
        } catch (Exception e) { 
            e.printStackTrace(); 
        } 
    } 
}