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
    // 3. PLAYFAIR CIPHER (UPDATED & VIVA-SAFE)
    // ==========================================
    public static char[][] generatePlayfairMatrix(String key) {
        char[][] matrix = new char[5][5];
        boolean[] seen = new boolean[26];
        seen['J' - 'A'] = true; // Treat J as I
        
        StringBuilder keyStr = new StringBuilder(key.toUpperCase().replaceAll("[^A-Z]", "").replace("J", "I"));
        for (char c = 'A'; c <= 'Z'; c++) {
            if (c != 'J') keyStr.append(c);
        }

        System.out.println("--- Playfair 5x5 Key Matrix ---");
        int index = 0;
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                while (seen[keyStr.charAt(index) - 'A']) {
                    index++;
                }
                matrix[r][c] = keyStr.charAt(index);
                seen[matrix[r][c] - 'A'] = true;
                System.out.print(matrix[r][c] + " ");
            }
            System.out.println();
        }
        return matrix;
    }

    private static int[] findPosition(char[][] matrix, char target) {
        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (matrix[r][c] == target) return new int[]{r, c};
            }
        }
        return null;
    }

    public static String playfairProcess(String text, String key, boolean encrypt) {
        char[][] matrix = generatePlayfairMatrix(key);
        text = text.toUpperCase().replaceAll("[^A-Z]", "").replace("J", "I");
        
        // Format digraphs
        StringBuilder formattedText = new StringBuilder();
        for (int i = 0; i < text.length(); i++) {
            formattedText.append(text.charAt(i));
            if (i + 1 < text.length() && text.charAt(i) == text.charAt(i + 1)) {
                formattedText.append('X'); // Insert X between double letters
            }
        }
        if (formattedText.length() % 2 != 0) formattedText.append('X');

        System.out.println("\nFormatted Digraphs: " + formattedText);
        System.out.println("--- Playfair Substitution Steps ---");

        StringBuilder result = new StringBuilder();
        
        // --- APPLIED CLEAR LOGIC FIX HERE ---
        int shift;
        if (encrypt) {
            shift = 1;
        } else {
            shift = -1;
        }

        for (int i = 0; i < formattedText.length(); i += 2) {
            char a = formattedText.charAt(i);
            char b = formattedText.charAt(i + 1);
            int[] posA = findPosition(matrix, a);
            int[] posB = findPosition(matrix, b);

            char newA, newB;
            if (posA[0] == posB[0]) { // Same Row
                newA = matrix[posA[0]][(posA[1] + shift + 5) % 5];
                newB = matrix[posB[0]][(posB[1] + shift + 5) % 5];
            } else if (posA[1] == posB[1]) { // Same Column
                newA = matrix[(posA[0] + shift + 5) % 5][posA[1]];
                newB = matrix[(posB[0] + shift + 5) % 5][posB[1]];
            } else { // Rectangle swap
                newA = matrix[posA[0]][posB[1]];
                newB = matrix[posB[0]][posA[1]];
            }
            System.out.println("Pair (" + a + b + ") -> (" + newA + newB + ")");
            result.append(newA).append(newB);
        }
        return result.toString();
    }
}