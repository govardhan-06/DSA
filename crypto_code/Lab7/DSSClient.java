import java.io.*; 
import java.net.*; 
import java.util.*; 
import java.math.BigInteger; 
import java.security.MessageDigest;

public class DSSClient { 
    static BigInteger p; 
    static BigInteger q; 
    static BigInteger g; 
    static Random rand = new Random(); 

    //modPow - built-in method for modular exponentiation
    //modInverse - built-in method for modular inverse
    //gcd - built-in method for greatest common divisor
    //hash function using SHA-512
 
    static BigInteger hash(String msg) throws Exception { 
        MessageDigest md = MessageDigest.getInstance("SHA-512"); 
        byte[] digest = md.digest(msg.getBytes()); 
        return new BigInteger(1, digest); 
    } 

    static String toHex(byte[] bytes) {
        StringBuilder hex = new StringBuilder();
        for (byte b : bytes) {
            hex.append(String.format("%02x", b));
        }
        return hex.toString();
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
        // Digital Signature Scheme (DSS) - Signature Generation Process
        // DSS uses DSA (Digital Signature Algorithm) variant
        // Components: p (large prime), q (factor of p-1), g (generator), private key x, public key y
        
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter prime number p: ");
        p = new BigInteger(sc.nextLine());
        System.out.print("Enter prime number q: ");
        q = new BigInteger(sc.nextLine());
        System.out.print("Enter generator g: ");
        g = new BigInteger(sc.nextLine());
        System.out.print("Enter Transaction: "); 
        String message = sc.nextLine(); 
 
        System.out.println("\n=== DSS SIGNATURE GENERATION ===");
        System.out.println("Step 1: Message = " + message);
        System.out.println("Step 2: Message bytes (hex) = " + toHex(message.getBytes()));
        
        // Phase 1: Hash the message
        System.out.println("Step 3: Computing SHA-512-based message hash H...");
        BigInteger H = hash(message).mod(q); 
        System.out.println("   H = hash(message) mod q = " + H); 
 
        // Phase 2: Generate key pair (x is private, y is public)
        System.out.println("\nPhase 2: Generate Key Pair");
        BigInteger x = randomBetween(BigInteger.ONE, q.subtract(BigInteger.ONE)); 
        System.out.println("Step 4: Generated private key x (1 < x < q) = " + x); 
 
        BigInteger y = g.modPow(x, p); 
        System.out.println("Step 5: Computed public key y = g^x mod p = " + y); 
 
        // Phase 3: Generate signature (r, s)
        System.out.println("\nPhase 3: Generate Signature Components (r, s)");
        BigInteger k; 
        do { 
            k = randomBetween(BigInteger.ONE, q.subtract(BigInteger.ONE)); 
        } while (!k.gcd(q).equals(BigInteger.ONE)); 
        System.out.println("Step 6: Selected random per-message key k (gcd(k,q)=1) = " + k); 
 
        BigInteger r = g.modPow(k, p).mod(q); 
        System.out.println("Step 7: Computed r = (g^k mod p) mod q = " + r); 
        
        BigInteger kInv = k.modInverse(q); 
        System.out.println("Step 8: Computed k^-1 mod q = " + kInv); 
        
        BigInteger s = (kInv.multiply(H.add(x.multiply(r)))).mod(q); 
        System.out.println("Step 9: Computed s = k^-1(H + xr) mod q = " + s);
        System.out.println("\nSignature = (r, s)"); 
 
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
        System.out.println("Message hash H = " + H); 
        System.out.println("Private key x = " + x); 
        System.out.println("Public key y = " + y); 
        System.out.println("Signature r = " + r); 
        System.out.println("Signature s = " + s); 
 
        socket.close(); 
        sc.close();
    } 
}