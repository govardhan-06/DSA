import java.io.*;
import java.net.*;
import java.util.Scanner;

public class DESClient {
    public static void main(String[] args) throws Exception {

        Socket socket = new Socket("localhost", 8050);
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter 64-bit binary key: ");
        String key = sc.nextLine();

        System.out.print("Enter 64-bit binary plaintext: ");
        String pt = sc.nextLine();

        String ct = DESUtil.encrypt(pt, key);

        System.out.println("\nCiphertext: " + ct);

        out.println(key);
        out.println(ct);

        socket.close();
        sc.close();
    }
}