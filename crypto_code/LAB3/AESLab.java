import java.util.Arrays;

public class AESLab {

    private static final int ROUNDS = 10;

    // AES S-Box
    private static final int[] SBOX = {
        0x63,0x7C,0x77,0x7B,0xF2,0x6B,0x6F,0xC5,0x30,0x01,0x67,0x2B,0xFE,0xD7,0xAB,0x76,
        0xCA,0x82,0xC9,0x7D,0xFA,0x59,0x47,0xF0,0xAD,0xD4,0xA2,0xAF,0x9C,0xA4,0x72,0xC0,
        0xB7,0xFD,0x93,0x26,0x36,0x3F,0xF7,0xCC,0x34,0xA5,0xE5,0xF1,0x71,0xD8,0x31,0x15,
        0x04,0xC7,0x23,0xC3,0x18,0x96,0x05,0x9A,0x07,0x12,0x80,0xE2,0xEB,0x27,0xB2,0x75,
        0x09,0x83,0x2C,0x1A,0x1B,0x6E,0x5A,0xA0,0x52,0x3B,0xD6,0xB3,0x29,0xE3,0x2F,0x84,
        0x53,0xD1,0x00,0xED,0x20,0xFC,0xB1,0x5B,0x6A,0xCB,0xBE,0x39,0x4A,0x4C,0x58,0xCF,
        0xD0,0xEF,0xAA,0xFB,0x43,0x4D,0x33,0x85,0x45,0xF9,0x02,0x7F,0x50,0x3C,0x9F,0xA8,
        0x51,0xA3,0x40,0x8F,0x92,0x9D,0x38,0xF5,0xBC,0xB6,0xDA,0x21,0x10,0xFF,0xF3,0xD2,
        0xCD,0x0C,0x13,0xEC,0x5F,0x97,0x44,0x17,0xC4,0xA7,0x7E,0x3D,0x64,0x5D,0x19,0x73,
        0x60,0x81,0x4F,0xDC,0x22,0x2A,0x90,0x88,0x46,0xEE,0xB8,0x14,0xDE,0x5E,0x0B,0xDB,
        0xE0,0x32,0x3A,0x0A,0x49,0x06,0x24,0x5C,0xC2,0xD3,0xAC,0x62,0x91,0x95,0xE4,0x79,
        0xE7,0xC8,0x37,0x6D,0x8D,0xD5,0x4E,0xA9,0x6C,0x56,0xF4,0xEA,0x65,0x7A,0xAE,0x08,
        0xBA,0x78,0x25,0x2E,0x1C,0xA6,0xB4,0xC6,0xE8,0xDD,0x74,0x1F,0x4B,0xBD,0x8B,0x8A,
        0x70,0x3E,0xB5,0x66,0x48,0x03,0xF6,0x0E,0x61,0x35,0x57,0xB9,0x86,0xC1,0x1D,0x9E,
        0xE1,0xF8,0x98,0x11,0x69,0xD9,0x8E,0x94,0x9B,0x1E,0x87,0xE9,0xCE,0x55,0x28,0xDF,
        0x8C,0xA1,0x89,0x0D,0xBF,0xE6,0x42,0x68,0x41,0x99,0x2D,0x0F,0xB0,0x54,0xBB,0x16
    };

    private static final int[] RCON = {
        0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36
    };

    // Print state as 4x4 matrix
    private static void printState(String msg, byte[] s) {
        System.out.println(msg);
        for (int i = 0; i < 16; i++) {
            System.out.printf("%02X ", s[i]);
            if ((i + 1) % 4 == 0) System.out.println();
        }
        System.out.println();
    }

    // SubBytes
    private static void subBytes(byte[] s) {
        for (int i = 0; i < 16; i++)
            s[i] = (byte) SBOX[s[i] & 0xFF];
    }

    // ShiftRows
    private static void shiftRows(byte[] s) {
        byte[] t = s.clone();
        s[1]=t[5];  s[5]=t[9];  s[9]=t[13]; s[13]=t[1];
        s[2]=t[10]; s[6]=t[14]; s[10]=t[2]; s[14]=t[6];
        s[3]=t[15]; s[7]=t[3];  s[11]=t[7]; s[15]=t[11];
    }

    // Galois Multiplication
    private static byte gmul(byte a, int b) {
        int p = 0;
        int aa = a & 0xFF;
        for (int i = 0; i < 8; i++) {
            if ((b & 1) != 0) p ^= aa;
            boolean hi = (aa & 0x80) != 0;
            aa <<= 1;
            if (hi) aa ^= 0x11B;
            b >>= 1;
        }
        return (byte) (p & 0xFF);
    }

    // MixColumns
    private static void mixColumns(byte[] s) {
        for (int i = 0; i < 4; i++) {
            int c = i * 4;
            byte a=s[c], b=s[c+1], c1=s[c+2], d=s[c+3];
            s[c]   = (byte)(gmul(a,2) ^ gmul(b,3) ^ c1 ^ d);
            s[c+1] = (byte)(a ^ gmul(b,2) ^ gmul(c1,3) ^ d);
            s[c+2] = (byte)(a ^ b ^ gmul(c1,2) ^ gmul(d,3));
            s[c+3] = (byte)(gmul(a,3) ^ b ^ c1 ^ gmul(d,2));
        }
    }

    // AddRoundKey
    private static void addRoundKey(byte[] s, byte[] k) {
        for (int i = 0; i < 16; i++)
            s[i] ^= k[i];
    }

    // Key Expansion (Simplified)
    private static byte[][] keyExpansion(byte[] key) {
        byte[][] roundKeys = new byte[11][16];
        roundKeys[0] = Arrays.copyOf(key, 16);

        for (int i = 1; i <= 10; i++) {
            byte[] prev = roundKeys[i - 1];
            byte[] temp = {prev[13], prev[14], prev[15], prev[12]};

            for (int j = 0; j < 4; j++)
                temp[j] = (byte) SBOX[temp[j] & 0xFF];

            temp[0] ^= RCON[i - 1];

            for (int j = 0; j < 16; j++) {
                if (j < 4)
                    roundKeys[i][j] = (byte) (prev[j] ^ temp[j]);
                else
                    roundKeys[i][j] = (byte) (prev[j] ^ roundKeys[i][j - 4]);
            }
        }
        return roundKeys;
    }

    // AES Encryption with Intermediate Steps
    public static String encrypt(String plaintext, String keyStr) {
        byte[] state = Arrays.copyOf(plaintext.getBytes(), 16);
        byte[] key = Arrays.copyOf(keyStr.getBytes(), 16);
        byte[][] roundKeys = keyExpansion(key);

        printState("Initial State:", state);

        addRoundKey(state, roundKeys[0]);
        printState("After AddRoundKey (Round 0):", state);

        for (int round = 1; round <= 9; round++) {
            System.out.println("----- Round " + round + " -----");
            subBytes(state);
            printState("After SubBytes:", state);

            shiftRows(state);
            printState("After ShiftRows:", state);

            mixColumns(state);
            printState("After MixColumns:", state);

            addRoundKey(state, roundKeys[round]);
            printState("After AddRoundKey:", state);
        }

        System.out.println("----- Final Round -----");
        subBytes(state);
        printState("After SubBytes:", state);

        shiftRows(state);
        printState("After ShiftRows:", state);

        addRoundKey(state, roundKeys[10]);
        printState("Cipher State:", state);

        return bytesToHex(state);
    }

    // Convert to Hex
    private static String bytesToHex(byte[] data) {
        StringBuilder sb = new StringBuilder();
        for (byte b : data)
            sb.append(String.format("%02X", b));
        return sb.toString();
    }

    // Main Method
    public static void main(String[] args) {
        String plaintext = "HELLOAESWORLD!!";   // 16 bytes
        String key = "ABCDEFGHIJKLMNOP";        // 16-byte key

        String cipher = encrypt(plaintext, key);
        System.out.println("Final Ciphertext: " + cipher);
    }
}