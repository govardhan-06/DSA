import java.net.*;
import java.io.*;
import java.util.Scanner;

public class AESClient {
    public static void main(String[] args) throws Exception {

        Socket s = new Socket("localhost", 8060);
        PrintWriter out = new PrintWriter(s.getOutputStream(), true);

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Plaintext: ");
        String pt = sc.nextLine();

        while (pt.length() < 16) pt += "X";
        pt = pt.substring(0, 16);

        String keyStr = "SECRETKEY1234567";

        int[][] state = AESCore.textToState(pt);
        int[][] key = AESCore.textToState(keyStr);

        AESCore.printState("Initial", state);

        AESCore.addRoundKey(state, key);
        AESCore.printState("After AddRoundKey", state);

        AESCore.subBytes(state);
        AESCore.printState("After SubBytes", state);

        AESCore.shiftRows(state);
        AESCore.printState("After ShiftRows", state);

        AESCore.mixColumns(state);
        AESCore.printState("After MixColumns", state);

        AESCore.addRoundKey(state, key);
        AESCore.printState("After Round1", state);

        String cipher = AESCore.stateToHex(state);
        System.out.println("Cipher: " + cipher);

        out.println(cipher);

        s.close();
    }
}