import java.io.*; 
import java.net.*; 
import java.util.*; 
import java.math.BigInteger; 

public class DSSClient { 
    // Small parameters as required by lab instructions
    static BigInteger p; 
    static BigInteger q; 
    static BigInteger g; 
    static Random rand = new Random(); 
 
    static BigInteger hash(String msg) { 
        int sum = 0; 
        for (char c : msg.toCharArray()) {
            sum += c; 
        }
        return BigInteger.valueOf(sum); 
    } 
 
    static BigInteger randomBetween(BigInteger min, BigInteger max) { 
        BigInteger range = max.subtract(min); 
        BigInteger result; 
        do { 
            result = new BigInteger(range.bitLength(), rand); 
        } while (result.compareTo(range) > 0); 
        return result.add(min); 
    } 
 
    public static void main(String[] args) throws Exception { 
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter prime number p: ");
        p = new BigInteger(sc.nextLine());
        System.out.print("Enter prime number q: ");
        q = new BigInteger(sc.nextLine());
        System.out.print("Enter generator g: ");
        g = new BigInteger(sc.nextLine());
        System.out.print("Enter Transaction: "); 
        String message = sc.nextLine(); 
 
        BigInteger H = hash(message); 
 
        // Private key x (1 < x < q) 
        BigInteger x = randomBetween(BigInteger.ONE, q.subtract(BigInteger.ONE)); 
 
        // Public key 
        BigInteger y = g.modPow(x, p); 
 
        // Random k for signature 
        BigInteger k; 
        do { 
            k = randomBetween(BigInteger.ONE, q.subtract(BigInteger.ONE)); 
        } while (!k.gcd(q).equals(BigInteger.ONE)); 
 
        // Signature Generation
        BigInteger r = g.modPow(k, p).mod(q); 
        BigInteger kInv = k.modInverse(q); 
        BigInteger s = (kInv.multiply(H.add(x.multiply(r)))).mod(q); 
 
        Socket socket = new Socket("localhost", 6000); 
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true); 
 
        // Send parameters 
        out.println(p); 
        out.println(q); 
        out.println(g); 
 
        // Send public key 
        out.println(y); 
 
        // Send message and signature 
        out.println(message); 
        out.println(r); 
        out.println(s); 
 
        System.out.println("\nTransaction Sent"); 
        System.out.println("Private key x = " + x); 
        System.out.println("Public key y = " + y); 
        System.out.println("Signature r = " + r); 
        System.out.println("Signature s = " + s); 
 
        socket.close(); 
        sc.close();
    } 
}