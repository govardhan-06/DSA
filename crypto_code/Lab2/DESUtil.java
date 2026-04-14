import java.util.Arrays;

/**
 * DESUtil - Simplified and Complete DES Implementation
 * ----------------------------------------------------
 * - Implements the full DES algorithm manually.
 * - Accepts plaintext strings and outputs hexadecimal ciphertext.
 * - Handles multiple blocks using PKCS#5 padding.
 * - Uses predefined Java utilities only for non-cryptographic tasks.
 */
public class DESUtil {

    /* ===================== PERMUTATION TABLES ===================== */

    // Initial Permutation (IP)
    static final int[] IP = {
        58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
    };

    // Final Permutation (FP)
    static final int[] FP = {
        40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
    };

    // Expansion Permutation (32 → 48 bits)
    static final int[] E = {
        32,1,2,3,4,5,4,5,6,7,8,9,
        8,9,10,11,12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,22,23,24,25,
        24,25,26,27,28,29,28,29,30,31,32,1
    };

    // Straight Permutation (P-Box)
    static final int[] P = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

    // Permuted Choice 1 (64 → 56 bits)
    static final int[] PC1 = {
        57,49,41,33,25,17,9,1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,21,13,5,28,20,12,4
    };

    // Permuted Choice 2 (56 → 48 bits)
    static final int[] PC2 = {
        14,17,11,24,1,5,3,28,15,6,21,10,
        23,19,12,4,26,8,16,7,27,20,13,2,
        41,52,31,37,47,55,30,40,51,45,33,48,
        44,49,39,56,34,53,46,42,50,36,29,32
    };

    // Number of left shifts for each round
    static final int[] SHIFTS = {
        1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
    };

    /* ===================== S-BOXES ===================== */

    static final int[][][] SBOX = {
        {   // S1
            {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
            {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
            {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
            {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
        },
        {   // S2
            {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
            {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
            {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
            {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
        },
        {   // S3
            {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
            {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
            {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
            {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
        },
        {   // S4
            {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
            {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
            {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
            {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
        },
        {   // S5
            {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
            {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
            {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
            {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
        },
        {   // S6
            {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
            {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
            {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
            {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
        },
        {   // S7
            {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
            {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
            {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
            {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
        },
        {   // S8
            {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
            {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
            {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
            {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
        }
    };

    /* ===================== UTILITY METHODS ===================== */

    // Generic permutation
    static long permute(long input, int[] table, int size) {
        long output = 0;
        for (int bit : table) {
            output = (output << 1) | ((input >>> (size - bit)) & 1L);
        }
        return output;
    }

    // Rotate 28-bit value
    static long rotateLeft28(long value, int shift) {
        return ((value << shift) | (value >>> (28 - shift))) & 0x0FFFFFFFL;
    }

    // Convert 8 bytes to long
    static long bytesToLong(byte[] bytes, int offset) {
        long value = 0;
        for (int i = 0; i < 8; i++) {
            value = (value << 8) | (bytes[offset + i] & 0xFFL);
        }
        return value;
    }

    // Convert long to 8 bytes
    static void longToBytes(long value, byte[] output, int offset) {
        for (int i = 7; i >= 0; i--) {
            output[offset + i] = (byte) (value & 0xFF);
            value >>>= 8;
        }
    }

    // Hex conversion utilities
    static String bytesToHex(byte[] bytes) {
        StringBuilder hex = new StringBuilder(bytes.length * 2);
        for (byte b : bytes)
            hex.append(String.format("%02X", b));
        return hex.toString();
    }

    static byte[] hexToBytes(String hex) {
        int len = hex.length();
        byte[] bytes = new byte[len / 2];
        for (int i = 0; i < len; i += 2)
            bytes[i / 2] = (byte) Integer.parseInt(hex.substring(i, i + 2), 16);
        return bytes;
    }

    /* ===================== DES CORE ===================== */

    // S-Box substitution
    static long sBoxSubstitution(long input48) {
        long output = 0;
        for (int i = 0; i < 8; i++) {
            int sixBits = (int) ((input48 >>> (42 - 6 * i)) & 0x3F);
            int row = ((sixBits & 0x20) >>> 4) | (sixBits & 0x01);
            int col = (sixBits >>> 1) & 0x0F;
            output = (output << 4) | SBOX[i][row][col];
        }
        return output;
    }

    // Feistel function
    static long feistel(long r, long key) {
        long expanded = permute(r, E, 32);
        long xored = expanded ^ key;
        long sboxed = sBoxSubstitution(xored);
        return permute(sboxed, P, 32);
    }

    // Key schedule
    static long[] generateKeys(String keyText) {
        byte[] keyBytes = Arrays.copyOf(keyText.getBytes(), 8);
        long key = bytesToLong(keyBytes, 0);

        long permKey = permute(key, PC1, 64);
        long c = (permKey >>> 28) & 0x0FFFFFFFL;
        long d = permKey & 0x0FFFFFFFL;

        long[] roundKeys = new long[16];
        for (int i = 0; i < 16; i++) {
            c = rotateLeft28(c, SHIFTS[i]);
            d = rotateLeft28(d, SHIFTS[i]);
            long combined = (c << 28) | d;
            roundKeys[i] = permute(combined, PC2, 56);
        }
        return roundKeys;
    }

    // Encrypt or decrypt a single 64-bit block
    static long encryptBlock(long block, long[] keys, boolean encrypt) {
        long ip = permute(block, IP, 64);
        long left = (ip >>> 32) & 0xFFFFFFFFL;
        long right = ip & 0xFFFFFFFFL;

        for (int i = 0; i < 16; i++) {
            long roundKey = encrypt ? keys[i] : keys[15 - i];
            long temp = right;
            right = left ^ feistel(right, roundKey);
            left = temp;
        }

        long combined = (right << 32) | left;
        return permute(combined, FP, 64);
    }

    /* ===================== PADDING ===================== */

    static byte[] pad(byte[] data) {
        int padding = 8 - (data.length % 8);
        byte[] padded = Arrays.copyOf(data, data.length + padding);
        Arrays.fill(padded, data.length, padded.length, (byte) padding);
        return padded;
    }

    static byte[] unpad(byte[] data) {
        int padding = data[data.length - 1];
        return Arrays.copyOf(data, data.length - padding);
    }

    /* ===================== PUBLIC API ===================== */

    public static String encryptText(String plaintext, String keyText) {
        byte[] padded = pad(plaintext.getBytes());
        long[] keys = generateKeys(keyText);
        byte[] cipherBytes = new byte[padded.length];

        for (int i = 0; i < padded.length; i += 8) {
            long block = bytesToLong(padded, i);
            long encrypted = encryptBlock(block, keys, true);
            longToBytes(encrypted, cipherBytes, i);
        }
        return bytesToHex(cipherBytes);
    }

    public static String decryptText(String cipherHex, String keyText) {
        byte[] cipherBytes = hexToBytes(cipherHex);
        long[] keys = generateKeys(keyText);
        byte[] plainBytes = new byte[cipherBytes.length];

        for (int i = 0; i < cipherBytes.length; i += 8) {
            long block = bytesToLong(cipherBytes, i);
            long decrypted = encryptBlock(block, keys, false);
            longToBytes(decrypted, plainBytes, i);
        }
        return new String(unpad(plainBytes));
    }

    /* ===================== MAIN METHOD ===================== */

    public static void main(String[] args) {
        String plaintext = "helloworld";
        String key = "mysecret";

        System.out.println("Plaintext : " + plaintext);

        String cipher = encryptText(plaintext, key);
        System.out.println("Ciphertext (Hex): " + cipher);

        String decrypted = decryptText(cipher, key);
        System.out.println("Decrypted : " + decrypted);
    }
}