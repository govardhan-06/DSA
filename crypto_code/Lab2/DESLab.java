public class SimpleDES {

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

    // Expansion Permutation (E)
    static final int[] E = {
        32,1,2,3,4,5,4,5,6,7,8,9,
        8,9,10,11,12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,22,23,24,25,
        24,25,26,27,28,29,28,29,30,31,32,1
    };

    // Permutation P
    static final int[] P = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

    // Key schedule tables
    static final int[] PC1 = {
        57,49,41,33,25,17,9,1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,21,13,5,28,20,12,4
    };

    static final int[] PC2 = {
        14,17,11,24,1,5,3,28,15,6,21,10,
        23,19,12,4,26,8,16,7,27,20,13,2,
        41,52,31,37,47,55,30,40,51,45,33,48,
        44,49,39,56,34,53,46,42,50,36,29,32
    };

    static final int[] SHIFTS = {
        1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
    };

    static long[] roundKeys = new long[16];

    // Utility: Permutation
    static long permute(long input, int[] table, int size) {
        long output = 0;
        for (int bit : table) {
            output = (output << 1) | ((input >>> (size - bit)) & 1);
        }
        return output;
    }

    // Rotate left for 28-bit halves
    static long rotateLeft28(long val, int shift) {
        return ((val << shift) | (val >>> (28 - shift))) & 0x0FFFFFFFL;
    }

    // Generate 16 round keys
    static void generateKeys(long key) {
        long permKey = permute(key, PC1, 64);
        long c = (permKey >>> 28) & 0x0FFFFFFFL;
        long d = permKey & 0x0FFFFFFFL;

        System.out.println("---- Key Schedule ----");
        for (int i = 0; i < 16; i++) {
            c = rotateLeft28(c, SHIFTS[i]);
            d = rotateLeft28(d, SHIFTS[i]);
            long combined = (c << 28) | d;
            roundKeys[i] = permute(combined, PC2, 56);
            System.out.printf("K%-2d: %048d%n", i + 1,
                    Long.parseUnsignedLong(Long.toBinaryString(roundKeys[i])));
        }
        System.out.println();
    }

    // Simplified Feistel Function
    static long feistel(long r, long key) {
        long expanded = permute(r, E, 32);
        long xored = expanded ^ key;
        long permuted = permute(xored, P, 48); // simplified (no S-box)
        return permuted & 0xFFFFFFFFL;
    }

    // DES Encryption
    static long encrypt(long plaintext, long key) {
        generateKeys(key);

        long ip = permute(plaintext, IP, 64);
        long L = (ip >>> 32) & 0xFFFFFFFFL;
        long R = ip & 0xFFFFFFFFL;

        System.out.println("After IP: L0=" + toBinary32(L) +
                           " R0=" + toBinary32(R));

        for (int i = 0; i < 16; i++) {
            long temp = R;
            R = L ^ feistel(R, roundKeys[i]);
            L = temp;

            System.out.println("Round " + (i + 1) +
                ": L=" + toBinary32(L) +
                " R=" + toBinary32(R));
        }

        long preOutput = (R << 32) | L;
        long cipher = permute(preOutput, FP, 64);
        return cipher;
    }

    // Binary formatting
    static String toBinary64(long val) {
        return String.format("%64s",
                Long.toBinaryString(val)).replace(' ', '0');
    }

    static String toBinary32(long val) {
        return String.format("%32s",
                Long.toBinaryString(val)).replace(' ', '0');
    }

    // Main method
    public static void main(String[] args) {
        long plaintext = 0x0123456789ABCDEFL;
        long key = 0x133457799BBCDFF1L;

        long cipher = encrypt(plaintext, key);

        System.out.println("\nCiphertext: " + toBinary64(cipher));
        System.out.printf("Ciphertext (Hex): %016X%n", cipher);
    }
}