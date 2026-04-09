import java.io.*;
import java.net.*;

public class DESServer {
    public static void main(String[] args) throws Exception {

        ServerSocket server = new ServerSocket(8050);
        System.out.println("Server running...");

        Socket socket = server.accept();

        BufferedReader in = new BufferedReader(
                new InputStreamReader(socket.getInputStream()));

        String key = in.readLine();
        String ct = in.readLine();

        System.out.println("\nReceived Cipher: " + ct);

        String pt = DESUtil.decrypt(ct, key);

        System.out.println("Decrypted: " + pt);

        socket.close();
        server.close();
    }
}