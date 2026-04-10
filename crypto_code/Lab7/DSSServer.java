import java.io.*; 
import java.net.*; 
import java.math.BigInteger;
import java.util.Scanner; 
import java.security.MessageDigest;

public class DSSServer { 
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
 
    public static void main(String[] args) throws Exception { 
        // Digital Signature Scheme (DSS) - Signature Verification Process
        // The verifier uses: message, signature (r,s), signer's public key y, and public parameters (p,q,g)
        // Verification succeeds if computed v equals r
        
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
 
        System.out.println("\n=== DSS SIGNATURE VERIFICATION ===");
        
        // Phase 1: Hash the received message
        System.out.println("Step 1: Message bytes (hex) = " + toHex(message.getBytes())); 
        System.out.println("Step 2: Computing SHA-512-based message hash H..."); 
        BigInteger H = hash(message).mod(q); 
        System.out.println("   H = hash(message) mod q = " + H); 
        
        // Phase 2: Compute verification parameters (w, u1, u2)
        System.out.println("\nPhase 2: Compute Verification Parameters");
        BigInteger w = sVal.modInverse(q); 
        System.out.println("Step 3: Computed w = s^-1 mod q = " + w); 
        
        BigInteger u1 = (H.multiply(w)).mod(q); 
        BigInteger u2 = (r.multiply(w)).mod(q); 
        System.out.println("Step 4: Computed u1 = (H * w) mod q = " + u1); 
        System.out.println("Step 5: Computed u2 = (r * w) mod q = " + u2); 
        
        // Phase 3: Compute verification value v and compare
        System.out.println("\nPhase 3: Verify Signature");
        BigInteger v = ((g.modPow(u1, p).multiply(y.modPow(u2, p))).mod(p)).mod(q); 
        
        System.out.println("Step 6: Computed v = ((g^u1 * y^u2) mod p) mod q = " + v);
        System.out.println("Step 7: Received r = " + r);
        System.out.println("Step 8: Does v equal r?");
 
        if (v.equals(r)) {
            System.out.println("\n✓ YES - Signature Verified. Transaction is Authentic."); 
        } else {
            System.out.println("\n✗ NO - Signature Invalid. Message Tampered or Signature Forged!"); 
        }
 
        s.close(); 
        ss.close(); 
    } 
}