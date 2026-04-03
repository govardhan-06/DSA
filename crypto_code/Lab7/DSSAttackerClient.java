import java.io.*; 
import java.net.*; 
import java.math.BigInteger; 
import java.util.Random;
import java.util.Scanner; 

public class DSSAttackerClient { 
    public static void main(String[] args) throws Exception { 
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter prime number p: ");
        BigInteger p = new BigInteger(sc.nextLine());
        System.out.print("Enter prime number q: ");
        BigInteger q = new BigInteger(sc.nextLine());
        System.out.print("Enter generator g: ");
        BigInteger g = new BigInteger(sc.nextLine());
        System.out.print("Enter malicious message: ");
        String message = sc.nextLine();
        
        Socket socket = new Socket("localhost", 6000); 
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true); 
        Random rand = new Random(); 
 
        BigInteger y = BigInteger.valueOf(rand.nextInt(10) + 1); 
 
        // Fake signature generated randomly
        BigInteger r = BigInteger.valueOf(rand.nextInt(10) + 1); 
        BigInteger s = BigInteger.valueOf(rand.nextInt(10) + 1); 
         
        // Send parameters
        out.println(p); 
        out.println(q); 
        out.println(g); 
        
        // Send public key
        out.println(y); 
        
        // Send message and fake signature
        out.println(message); 
        out.println(r); 
        out.println(s); 
 
        System.out.println("\nMalicious transaction sent!"); 
        System.out.println("Fake r = " + r); 
        System.out.println("Fake s = " + s); 
        
        socket.close(); 
    } 
}