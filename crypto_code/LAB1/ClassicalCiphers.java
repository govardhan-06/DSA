public class ClassicalCiphers {

    // ==========================================
    // 1. CAESAR CIPHER
    // ==========================================
    public static String caesarEncrypt(String plainText, int shift) {
        System.out.println("--- Caesar Substitution Steps ---");
        StringBuilder cipher = new StringBuilder();
        for (char c : plainText.toUpperCase().toCharArray()) {
            if (Character.isLetter(c)) {
                char enc = (char) (((c - 'A' + shift) % 26) + 'A');
                System.out.println(c + " -> Shifted by " + shift + " -> " + enc);
                cipher.append(enc);
            }
        }
        return cipher.toString();
    }

    public static String caesarDecrypt(String cipherText, int shift) {
        StringBuilder plain = new StringBuilder();
        for (char c : cipherText.toUpperCase().toCharArray()) {
            if (Character.isLetter(c)) {
                char dec = (char) (((c - 'A' - shift + 26) % 26) + 'A');
                plain.append(dec);
            }
        }
        return plain.toString();
    }

    // ==========================================
    // 2. VIGENÈRE CIPHER
    // ==========================================
    public static String generateVigenereKey(String text, String key) {
        StringBuilder extendedKey = new StringBuilder(key);
        while (extendedKey.length() < text.length()) {
            extendedKey.append(key);
        }
        return extendedKey.substring(0, text.length()).toUpperCase();
    }

    public static String vigenereEncrypt(String plainText, String key) {
        plainText = plainText.toUpperCase().replaceAll("[^A-Z]", "");
        String extKey = generateVigenereKey(plainText, key);
        
        System.out.println("--- Vigenere Intermediate Steps ---");
        System.out.println("Plaintext: " + plainText);
        System.out.println("Aligned Key: " + extKey);
        
        StringBuilder cipher = new StringBuilder();
        for (int i = 0; i < plainText.length(); i++) {
            char p = plainText.charAt(i);
            char k = extKey.charAt(i);
            char c = (char) (((p - 'A') + (k - 'A')) % 26 + 'A');
            System.out.println("P: " + p + " + K: " + k + " = C: " + c);
            cipher.append(c);
        }
        return cipher.toString();
    }

    public static String vigenereDecrypt(String cipherText, String key) {
        String extKey = generateVigenereKey(cipherText, key);
        StringBuilder plain = new StringBuilder();
        for (int i = 0; i < cipherText.length(); i++) {
            char c = cipherText.charAt(i);
            char k = extKey.charAt(i);
            char p = (char) (((c - 'A') - (k - 'A') + 26) % 26 + 'A');
            plain.append(p);
        }
        return plain.toString();
    }

    // ==========================================
    // 3. PLAYFAIR CIPHER
    // ==========================================
    public static char[][] generate Matrix(String key) {
                                                                                                                 char[][] matrix = new char[5][5];
        boolean[] used = new boolean[26];

        key = key.toUpperCase().replaceAll("[^A-Z]", "").replace('J', 'I');

        StringBuilder sb = new StringBuilder();

        // Add key characters without duplicates.
        for (char c : key.toCharArray()) {
            if (!used[c - 'A']) {
                used[c - 'A'] = true;
                sb.append(c);
            }
        }

        // Add remaining letters except J.
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c != 'J' && !used[c - 'A']) {
                sb.append(c);
            }
        }

        int index = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                matrix[i][j] = sb.charAt(index++);
            }
        }

        return matrix;
    }

    private static int[] findPosition(char[][] matrix, char ch) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (matrix[i][j] == ch) {
                    return new int[]{i, j};
                }
            }
        }
        return null;
    }

    private static String prepareText(String text) {
        text = text.toUpperCase().replaceAll("[^A-Z]", "").replace('J', 'I');
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < text.length(); i++) {
            char a = text.charAt(i);
            char b = (i + 1 < text.length()) ? text.charAt(i + 1) : 'X';

            if (a == b) {
                sb.append(a).append('X');
            } else {
                sb.append(a).append(b);
                i++; // Move to next pair.
            }
        }

        if (sb.length() % 2 != 0) {
            sb.append('X');
        }

        return sb.toString();
    }

    public static String process(String text, String key, boolean encrypt) {
        char[][] matrix = generateMatrix(key);
        String prepared = prepareText(text);
        StringBuilder result = new StringBuilder();

        int shift = encrypt ? 1 : -1;

        for (int i = 0; i < prepared.length(); i += 2) {
            char a = prepared.charAt(i);
            char b = prepared.charAt(i + 1);

            int[] posA = findPosition(matrix, a);
            int[] posB = findPosition(matrix, b);

            if (posA[0] == posB[0]) {
                result.append(matrix[posA[0]][  
                result.append(matrix[posB[0]][(posB[1] + shift + 5) % 5]);
            } else if (posA[1] == posB[1]) {
                result.append(matrix[(posA[0] + shift + 5) % 5][posA[1]]);
                result.append(matrix[(posB[0] + shift + 5) % 5][posB[1]]);
            } else {
                result.append(matrix[posA[0]][posB[1]]);
                result.append(matrix[posB[0]][posA[1]]);
            }
        }

        return result.toString();
    }

    public static String encrypt(String plaintext, String key) {
        return process(plaintext, key, true);
    }

    public static String decrypt(String ciphertext, String key) {
        return process(ciphertext, key, false);
    }

    public static void printMatrix(char[][] matrix) {
        for (char[] row : matrix) {
            for (char c : row) {
                System.out.print(c + " ");
            } 
            System.out.println();
        }
    }

    // Backward-compatible wrappers for existing callers.
    public static char[][] generatePlayfairMatrix(String key) {
        return generateMatrix(key);
    }

    public static String playfairProcess(String text, String key, boolean encrypt) {
        return process(text, key, encrypt);
    }
}