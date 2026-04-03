import java.io.ByteArrayOutputStream;
import java.security.MessageDigest;

public class HMACCore {
    // SHA-512 Block Size is 1024 bits (128 bytes)
    private static final int BLOCK_SIZE = 128; 

    // Raw hashing wrapper
    private static byte[] sha512(byte[] input) throws Exception {
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        return md.digest(input);
    }

    // The manual HMAC implementation
    public static String calculateHMAC(String key, String message) throws Exception {
        byte[] keyBytes = key.getBytes("UTF-8");
        byte[] msgBytes = message.getBytes("UTF-8");

        // Step 1: Format Key to exactly 128 bytes
        if (keyBytes.length > BLOCK_SIZE) {
            keyBytes = sha512(keyBytes); // Hash it if it's too long
        }
        
        byte[] kPrime = new byte[BLOCK_SIZE];
        System.arraycopy(keyBytes, 0, kPrime, 0, keyBytes.length); // Pad with zeros

        // Step 2: Create inner pad (ipad) and outer pad (opad)
        byte[] iPad = new byte[BLOCK_SIZE];
        byte[] oPad = new byte[BLOCK_SIZE];

        for (int i = 0; i < BLOCK_SIZE; i++) {
            iPad[i] = (byte) (kPrime[i] ^ 0x36);
            oPad[i] = (byte) (kPrime[i] ^ 0x5C);
        }

        System.out.println("--- HMAC Intermediate Computations ---");
        System.out.println("Key padded (K'): " + bytesToHex(kPrime).substring(0, 32) + "... (truncated)");
        System.out.println("Inner Pad (K' XOR 0x36): " + bytesToHex(iPad).substring(0, 32) + "...");
        System.out.println("Outer Pad (K' XOR 0x5C): " + bytesToHex(oPad).substring(0, 32) + "...");

        // Step 3: Compute Inner Hash = SHA-512(iPad || message)
        ByteArrayOutputStream innerStream = new ByteArrayOutputStream();
        innerStream.write(iPad);
        innerStream.write(msgBytes);
        byte[] innerHash = sha512(innerStream.toByteArray());
        
        System.out.println("Inner Hash = SHA-512(iPad || msg): \n" + bytesToHex(innerHash));

        // Step 4: Compute Outer Hash = SHA-512(oPad || innerHash) -> Final MAC
        ByteArrayOutputStream outerStream = new ByteArrayOutputStream();
        outerStream.write(oPad);
        outerStream.write(innerHash);
        byte[] finalMAC = sha512(outerStream.toByteArray());

        return bytesToHex(finalMAC);
    }

    // Helper: Convert bytes to Hex string
    public static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }
}