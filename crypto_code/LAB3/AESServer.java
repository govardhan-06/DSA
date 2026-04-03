import java.net.*;
import java.io.*;

public class AESServer {
    public static void main(String[] args) throws Exception {

        ServerSocket ss = new ServerSocket(8060);
        System.out.println("Server Started...");

        Socket s = ss.accept();

        BufferedReader in = new BufferedReader(
                new InputStreamReader(s.getInputStream()));

        String cipher = in.readLine();

        System.out.println("Received Cipher: " + cipher);
        System.out.println("Decryption Step (Concept Demonstrated)");

        ss.close();
    }
}