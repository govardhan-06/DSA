class DESUtil {

    static final int[] IP = {
        58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
    };

    static final int[] FP = {
        40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
    };

    static final int[] E = {
        32,1,2,3,4,5,4,5,6,7,8,9,
        8,9,10,11,12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,22,23,24,25,
        24,25,26,27,28,29,28,29,30,31,32,1
    };

    static final int[] P = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

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

    public static long[] ROUND_KEYS = new long[16];

    static long binaryToLong(String bin) {
        if (bin == null || bin.length() != 64 || !bin.matches("[01]{64}")) {
            throw new IllegalArgumentException("Input must be exactly 64 bits");
        }
        return Long.parseUnsignedLong(bin, 2);
    }

    static String formatBinary(long value, int width) {
        String bits = Long.toBinaryString(value);
        if (bits.length() > width) {
            bits = bits.substring(bits.length() - width);
        }
        return String.format("%" + width + "s", bits).replace(' ', '0');
    }

    static String longToBinary(long val) {
        return formatBinary(val, 64);
    }

    static String toBinary32(long val) {
        return formatBinary(val & 0xFFFFFFFFL, 32);
    }

    static String toBinary48(long val) {
        return formatBinary(val & 0xFFFFFFFFFFFFL, 48);
    }

    static long permute(long input, int[] table, int size) {
        long output = 0;
        for (int bit : table) {
            output = (output << 1) | ((input >>> (size - bit)) & 1L);
        }
        return output;
    }

    static long rotateLeft28(long value, int shift) {
        return ((value << shift) | (value >>> (28 - shift))) & 0x0FFFFFFFL;
    }

    public static long[] generateKeys(String keyBin) {
        return generateKeys(binaryToLong(keyBin));
    }

    public static long[] generateKeys(long key) {
        long permKey = permute(key, PC1, 64);
        long c = (permKey >>> 28) & 0x0FFFFFFFL;
        long d = permKey & 0x0FFFFFFFL;

        System.out.println("Key Schedule");
        System.out.println("PC-1 Output: " + formatBinary(permKey, 56));

        for (int i = 0; i < 16; i++) {
            c = rotateLeft28(c, SHIFTS[i]);
            d = rotateLeft28(d, SHIFTS[i]);
            long combined = (c << 28) | d;
            ROUND_KEYS[i] = permute(combined, PC2, 56);
            System.out.println("K" + (i + 1) + ": " + toBinary48(ROUND_KEYS[i]));
        }

        return ROUND_KEYS.clone();
    }

    static long feistel(long r, long key) {
        long expanded = permute(r, E, 32);
        long xored = expanded ^ key;
        return permute(xored, P, 48);
    }

    static String process(String block, String keyBin, boolean encrypting) {
        long data = binaryToLong(block);
        long[] keys = generateKeys(keyBin);

        System.out.println();
        System.out.println(encrypting ? "Encryption" : "Decryption");
        System.out.println("Input:  " + longToBinary(data));

        long ip = permute(data, IP, 64);
        long left = (ip >>> 32) & 0xFFFFFFFFL;
        long right = ip & 0xFFFFFFFFL;

        System.out.println("After IP: L0=" + toBinary32(left) + " R0=" + toBinary32(right));

        for (int round = 0; round < 16; round++) {
            int keyIndex = encrypting ? round : 15 - round;
            long roundKey = keys[keyIndex];
            long fOut = feistel(right, roundKey) & 0xFFFFFFFFL;
            long nextLeft = right;
            long nextRight = (left ^ fOut) & 0xFFFFFFFFL;

            System.out.println(
                "Round " + (round + 1) +
                " [K" + (keyIndex + 1) + "]" +
                ": L=" + toBinary32(nextLeft) +
                " R=" + toBinary32(nextRight) +
                " F=" + toBinary32(fOut)
            );

            left = nextLeft;
            right = nextRight;
        }

        long combined = ((right & 0xFFFFFFFFL) << 32) | (left & 0xFFFFFFFFL);
        System.out.println("Pre-output (R16||L16): " + longToBinary(combined));

        long output = permute(combined, FP, 64);
        System.out.println("Final Permutation: " + longToBinary(output));

        return longToBinary(output);
    }

    public static String encrypt(String plaintext, String keyBin) {
        return process(plaintext, keyBin, true);
    }

    public static String decrypt(String ciphertext, String keyBin) {
        return process(ciphertext, keyBin, false);
    }
}