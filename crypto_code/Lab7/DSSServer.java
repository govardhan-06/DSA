import java.io.*; 
import java.net.*; 
import java.math.BigInteger;
import java.util.Scanner; 

public class DSSServer { 
    // Dummy hash function to avoid built-in libraries per lab rules
    static BigInteger hash(String msg) { 
        int sum = 0; 
        for (char c : msg.toCharArray()) {
            sum += c; 
        }
        return BigInteger.valueOf(sum); 
    } 
 
    public static void main(String[] args) throws Exception { 
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter prime number p: ");
        BigInteger p = new BigInteger(sc.nextLine());
        System.out.print("Enter prime number q: ");
        BigInteger q = new BigInteger(sc.nextLine());
        System.out.print("Enter generator g: ");
        BigInteger g = new BigInteger(sc.nextLine());
        
        ServerSocket ss = new ServerSocket(6000); 
        System.out.println("\nBank Server Waiting on port 6000..."); 
        Socket s = ss.accept(); 
        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream())); 
 
        // Receive public key 
        BigInteger y = new BigInteger(br.readLine()); 
 
        // Receive message and signature 
        String message = br.readLine(); 
        BigInteger r = new BigInteger(br.readLine()); 
        BigInteger sVal = new BigInteger(br.readLine()); 
 
        System.out.println("\nTransaction Received: " + message); 
        System.out.println("Public Key y = " + y); 
        System.out.println("Signature r = " + r + "\nSignature s = " + sVal); 
 
        // Verification Process
        BigInteger H = hash(message); 
        BigInteger w = sVal.modInverse(q); 
        BigInteger u1 = (H.multiply(w)).mod(q); 
        BigInteger u2 = (r.multiply(w)).mod(q); 
 
        BigInteger v = ((g.modPow(u1, p).multiply(y.modPow(u2, p))).mod(p)).mod(q); 
        
        System.out.println("\nCalculated v = " + v);
 
        if (v.equals(r)) {
            System.out.println("Signature Verified. Transaction Authentic."); 
        } else {
            System.out.println("Signature Invalid. Message Tampered!"); 
        }
 
        s.close(); 
        ss.close(); 
    } 
}