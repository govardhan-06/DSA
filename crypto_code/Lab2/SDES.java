public class SDES {

    // Permutation Tables
    static final int[] P10 = {3,5,2,7,4,10,1,9,8,6};
    static final int[] P8  = {6,3,7,4,8,5,10,9};
    static final int[] IP  = {2,6,3,1,4,8,5,7};
    static final int[] EP  = {4,1,2,3,2,3,4,1};
    static final int[] P4  = {2,4,3,1};
    static final int[] IP_INV = {4,1,3,5,7,2,8,6};

    // S-Boxes
    static final int[][] S0 = {
        {1,0,3,2},
        {3,2,1,0},
        {0,2,1,3},
        {3,1,3,2}
    };

    static final int[][] S1 = {
        {0,1,2,3},
        {2,0,1,3},
        {3,0,1,0},
        {2,1,0,3}
    };

    public static int[] K1 = new int[8];
    public static int[] K2 = new int[8];

    // ---------------- PERMUTATION ----------------
    public static int[] permute(int[] input, int[] table) {
        int[] output = new int[table.length];
        for (int i = 0; i < table.length; i++)
            output[i] = input[table[i] - 1];
        return output;
    }

    // ---------------- LEFT SHIFT ----------------
    public static int[] leftShift(int[] input, int shifts) {
        int half = input.length / 2;
        int[] output = new int[input.length];

        for (int i = 0; i < half; i++) {
            output[i] = input[(i + shifts) % half];
            output[i + half] = input[half + (i + shifts) % half];
        }
        return output;
    }

    // ---------------- KEY GENERATION ----------------
    public static void generateKeys(String keyStr) {
        if (keyStr.length() != 10) {
            throw new IllegalArgumentException("Key must be 10 bits");
        }

        int[] key = new int[10];
        for (int i = 0; i < 10; i++)
            key[i] = keyStr.charAt(i) - '0';

        int[] p10 = permute(key, P10);
        int[] ls1 = leftShift(p10, 1);

        K1 = permute(ls1, P8);

        int[] ls2 = leftShift(ls1, 2);
        K2 = permute(ls2, P8);

        System.out.println("K1: " + arr(K1));
        System.out.println("K2: " + arr(K2));
    }

    // ---------------- F FUNCTION ----------------
    public static int[] f(int[] R, int[] K) {

        int[] ep = permute(R, EP);

        int[] xor = new int[8];
        for (int i = 0; i < 8; i++)
            xor[i] = ep[i] ^ K[i];

        // S0
        int row = xor[0]*2 + xor[3];
        int col = xor[1]*2 + xor[2];
        int val0 = S0[row][col];

        // S1
        row = xor[4]*2 + xor[7];
        col = xor[5]*2 + xor[6];
        int val1 = S1[row][col];

        int[] sbox = {
            val0 / 2, val0 % 2,
            val1 / 2, val1 % 2
        };

        return permute(sbox, P4);
    }

    // ---------------- MAIN DES PROCESS ----------------
    public static String processDES(String text, int[] k1, int[] k2) {

        if (text.length() != 8)
            throw new IllegalArgumentException("Text must be 8 bits");

        int[] input = new int[8];
        for (int i = 0; i < 8; i++)
            input[i] = text.charAt(i) - '0';

        System.out.println("\nInput: " + arr(input));

        int[] ip = permute(input, IP);

        int[] L = {ip[0], ip[1], ip[2], ip[3]};
        int[] R = {ip[4], ip[5], ip[6], ip[7]};

        System.out.println("After IP: L=" + arr(L) + " R=" + arr(R));

        // ROUND 1
        int[] f1 = f(R, k1);
        int[] L1 = R;
        int[] R1 = xor(L, f1);

        System.out.println("Round1: L=" + arr(L1) + " R=" + arr(R1));

        // ROUND 2
        int[] f2 = f(R1, k2);
        int[] L2 = xor(L1, f2);
        int[] R2 = R1;

        System.out.println("Round2: L=" + arr(L2) + " R=" + arr(R2));

        int[] combined = {
            L2[0],L2[1],L2[2],L2[3],
            R2[0],R2[1],R2[2],R2[3]
        };

        int[] output = permute(combined, IP_INV);

        return arr(output).replace(" ", "");
    }

    // ---------------- UTILS ----------------
    public static int[] xor(int[] a, int[] b) {
        int[] res = new int[a.length];
        for (int i = 0; i < a.length; i++)
            res[i] = a[i] ^ b[i];
        return res;
    }

    public static String arr(int[] a) {
        StringBuilder sb = new StringBuilder();
        for (int i : a) sb.append(i).append(" ");
        return sb.toString().trim();
    }
}