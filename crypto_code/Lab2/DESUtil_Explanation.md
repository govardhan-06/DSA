# DESUtil.java - Complete Line-by-Line Explanation

## Overview

This is a complete implementation of the **Data Encryption Standard (DES)** algorithm in Java. DES is a symmetric encryption algorithm that processes data in 64-bit blocks using a 56-bit key.

---

## 1. IMPORTS & CLASS DECLARATION

```java
import java.util.Arrays;
```

- Imports the `Arrays` utility class for array operations like `copyOf()` and `fill()` used in padding/unpadding.

```java
public class DESUtil {
```

- Declares the main utility class containing all DES operations.

---

## 2. PERMUTATION TABLES SECTION

### What are Permutations?

Permutations reorder bits according to predefined tables. DES uses several permutation tables for security and algorithm specification.

### 2.1 Initial Permutation (IP)

```java
static final int[] IP = {
    58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
};
```

- **Purpose**: Reorders the 64-bit input block before starting DES rounds.
- **Values**: Each number (1-64) represents a bit position.
- **Meaning**: The first output bit comes from input bit 58, second from bit 50, etc.
- **Size**: 64 elements (for 64 bits)

### 2.2 Final Permutation (FP)

```java
static final int[] FP = {
    40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
};
```

- **Purpose**: Inverse of Initial Permutation, applied after all 16 rounds.
- **Size**: 64 elements (for 64 bits)
- **Note**: IP and FP are inverses of each other (mathematically: FP = IP⁻¹)

### 2.3 Expansion Permutation (E)

```java
static final int[] E = {
    32,1,2,3,4,5,4,5,6,7,8,9,
    8,9,10,11,12,13,12,13,14,15,16,17,
    16,17,18,19,20,21,20,21,22,23,24,25,
    24,25,26,27,28,29,28,29,30,31,32,1
};
```

- **Purpose**: Expands 32-bit right half to 48 bits for XOR with 48-bit subkey.
- **Note**: Some bit positions are repeated (e.g., 1 appears twice), allowing bit reuse.
- **Size**: 48 elements

### 2.4 Straight Permutation (P-Box)

```java
static final int[] P = {
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};
```

- **Purpose**: Permutes 32-bit S-Box output back to 32 bits.
- **Size**: 32 elements

### 2.5 Permuted Choice 1 (PC1) - Key Schedule

```java
static final int[] PC1 = {
    57,49,41,33,25,17,9,1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,21,13,5,28,20,12,4
};
```

- **Purpose**: Reduces 64-bit key to 56 bits by removing parity bits (positions 8, 16, 24, 32, etc.).
- **Size**: 56 elements (one parity bit removed every 8 bits)

### 2.6 Permuted Choice 2 (PC2) - Key Schedule

```java
static final int[] PC2 = {
    14,17,11,24,1,5,3,28,15,6,21,10,
    23,19,12,4,26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,51,45,33,48,
    44,49,39,56,34,53,46,42,50,36,29,32
};
```

- **Purpose**: Selects and permutes 48 bits from 56-bit key source for each round key.
- **Size**: 48 elements (selects 48 of 56 bits)

### 2.7 Round Shift Table (SHIFTS)

```java
static final int[] SHIFTS = {
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};
```

- **Purpose**: Defines how many positions to rotate key halves in each of 16 rounds.
- **Meaning**:
  - Round 1: rotate by 1
  - Round 2: rotate by 1
  - Rounds 3-8: rotate by 2
  - Round 9: rotate by 1
  - Rounds 10-15: rotate by 2
  - Round 16: rotate by 1

---

## 3. S-BOXES (SUBSTITUTION BOXES) SECTION

```java
static final int[][][] SBOX = {
    {   // S1
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {   // S2 through S8...
    }
};
```

### What are S-Boxes?

- **Purpose**: Provide non-linearity to DES (main source of security).
- **Structure**: 8 different S-Boxes (S0 through S7), each with 4 rows and 16 columns.
- **Input**: 6 bits
- **Output**: 4 bits
- **Usage**: 8 × 6-bit = 48 bits → 8 × 4-bit = 32 bits

### How S-Box Substitution Works

For a 6-bit input:

- **Bits 1 & 6** (first and last) → determine **row** (0-3)
- **Bits 2-5** (middle) → determine **column** (0-15)
- **Output**: The value at that row/column

**Example (S1, 6-bit input: 011011):**

- Row = 01 (first bit) + 1 (last bit) = 2 (row 2)
- Column = 1101 (middle bits) = 13 (column 13)
- Output = SBOX[0][2][13] = 0

---

## 4. UTILITY FUNCTIONS SECTION

### 4.1 Generic Permutation Function

```java
static long permute(long input, int[] table, int size) {
    long output = 0;
    for (int bit : table) {
        output = (output << 1) | ((input >>> (size - bit)) & 1L);
    }
    return output;
}
```

**Parameters:**

- `input`: The number whose bits are being rearranged
- `table`: Permutation table defining new bit order
- `size`: Total bit size (64, 56, 48, 32, etc.)

**Logic:**

1. `for (int bit : table)` - Loop through each value in permutation table
2. `output = (output << 1)` - Shift output left by 1 position
3. `((input >>> (size - bit)) & 1L)` - Extract the bit at position "bit" from input
   - `size - bit`: Calculate bit position from the right
   - `>>> (size - bit)`: Shift to move that bit to position 0
   - `& 1L`: Mask to get only that bit (1 or 0)
4. `|` - Place extracted bit into output

**Example:** If table = [2, 1, 3], input = 0b1010 (size=4):

- Extract bit 2: (1010 >> 2) & 1 = 0
- Extract bit 1: (1010 >> 3) & 1 = 1
- Extract bit 3: (1010 >> 1) & 1 = 1
- Result: 011 (binary) = 3

### 4.2 Circular Left Rotate (28-bit)

```java
static long rotateLeft28(long value, int shift) {
    return ((value << shift) | (value >>> (28 - shift))) & 0x0FFFFFFFL;
}
```

**Purpose**: Rotate a 28-bit key half for key schedule.

**Logic:**

1. `(value << shift)` - Shift left by "shift" positions
2. `(value >>> (28 - shift))` - Bits that "fall off" on the left wrap around on the right
3. `|` - Combine the two parts
4. `& 0x0FFFFFFFL` - Mask to keep only 28 bits (0x0FFFFFF = 28 ones in binary)

**Example:** Rotate 0x1234567 left by 1 (28-bit):

- Left shift: 0x2468ACE
- Right wrap: 0x0000000 (bit fell off at position 28)
- Result: 0x2468ACE

### 4.3 S-Box Substitution (48 → 32 bits)

```java
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
```

**Purpose**: Apply all 8 S-Boxes to convert 48 bits to 32 bits.

**Logic:**

- Loop through 8 S-Boxes
- `(input48 >>> (42 - 6 * i)) & 0x3F` - Extract 6 bits for S-Box i
  - `42 - 6*i` extracts bits: [47-42], [41-36], [35-30], etc.
  - `0x3F` = 0b111111 (6 ones) to mask 6 bits
- `row = ((sixBits & 0x20) >>> 4) | (sixBits & 0x01)` - Extract bits 6 and 1 (row index)
- `col = (sixBits >>> 1) & 0x0F` - Extract bits 5-2 (column index)
- `SBOX[i][row][col]` - Look up value in S-Box
- `output = (output << 4) | result` - Append 4-bit result to output

### 4.4 Feistel Function

```java
static long feistel(long r, long key) {
    long expanded = permute(r, E, 32);
    long xored = expanded ^ key;
    long sboxed = sBoxSubstitution(xored);
    return permute(sboxed, P, 32);
}
```

**Purpose**: Core DES round transformation.

**Steps:**

1. `permute(r, E, 32)` - Expand 32 bits to 48 bits using E-table
2. `expanded ^ key` - XOR with 48-bit round key
3. `sBoxSubstitution(xored)` - Apply 8 S-Boxes to compress back to 32 bits
4. `permute(sboxed, P, 32)` - Final permutation

---

## 5. KEY GENERATION SECTION

```java
static long[] generateKeys(byte[] keyBytes) {
    long key = 0;
    for (byte b : keyBytes) {
        key = (key << 8) | (b & 0xFF);
    }
```

- Converts 8 bytes to a single 64-bit long value
- `key << 8` shifts previous value left by 8 bits
- `(b & 0xFF)` converts signed byte to unsigned (0-255)
- `|` combines all bytes into one 64-bit number

```java
    long permKey = permute(key, PC1, 64);
```

- Apply PC1 permutation to remove parity bits: 64 → 56 bits

```java
    long c = (permKey >>> 28) & 0x0FFFFFFFL;
    long d = permKey & 0x0FFFFFFFL;
```

- Split 56 bits into two 28-bit halves:
  - `c`: Left half (bits 55-28)
  - `d`: Right half (bits 27-0)
  - `0x0FFFFFF` = 28 ones in binary

```java
    long[] roundKeys = new long[16];
    for (int i = 0; i < 16; i++) {
        c = rotateLeft28(c, SHIFTS[i]);
        d = rotateLeft28(d, SHIFTS[i]);
```

- Create array for 16 round keys (one per round)
- For each round, rotate both halves according to SHIFTS table

```java
        long combined = (c << 28) | d;
        roundKeys[i] = permute(combined, PC2, 56);
    }
    return roundKeys;
```

- Combine rotated halves back to 56 bits
- Apply PC2 permutation: 56 → 48 bits (select specific positions)
- Store as round key

---

## 6. BLOCK ENCRYPTION SECTION

```java
static long encryptBlock(long block, long[] keys, boolean encrypt) {
    long ip = permute(block, IP, 64);
```

- Apply Initial Permutation to reorder input bits

```java
    long left = (ip >>> 32) & 0xFFFFFFFFL;
    long right = ip & 0xFFFFFFFFL;
```

- Split 64-bit permuted block into two 32-bit halves
- `left`: bits 63-32 (upper half)
- `right`: bits 31-0 (lower half)

```java
    for (int i = 0; i < 16; i++) {
        long roundKey = encrypt ? keys[i] : keys[15 - i];
```

- Perform 16 Feistel rounds
- **Encryption**: Use keys in forward order (0-15)
- **Decryption**: Use keys in reverse order (15-0)

```java
        long temp = right;
        right = left ^ feistel(right, roundKey);
        left = temp;
    }
```

- **Feistel swap**:
  1. Save right half to temp
  2. New right = left XOR feistel(right, key)
  3. New left = old right (swap)
  - This ensures invertibility (same operation for decrypt)

```java
    long combined = (right << 32) | left;
    return permute(combined, FP, 64);
```

- After 16 rounds, combine halves (note: RIGHT comes first after swaps)
- Apply Final Permutation to get ciphertext

---

## 7. PADDING SECTION

### 7.1 PKCS#5 Padding

```java
static byte[] pad(byte[] data) {
    int padding = 8 - (data.length % 8);
    byte[] padded = Arrays.copyOf(data, data.length + padding);
    Arrays.fill(padded, data.length, padded.length, (byte) padding);
    return padded;
}
```

**Purpose**: Ensure data is multiple of 8 bytes for DES.

**Logic:**

- `8 - (data.length % 8)` - Calculate how many bytes needed to reach multiple of 8
- `Arrays.copyOf(data, data.length + padding)` - Create new array with extra space
- `Arrays.fill(padded, data.length, padded.length, (byte) padding)` - Fill padding bytes with padding value

**Example:** "hello" (5 bytes)

- Padding needed: 8 - (5 % 8) = 3
- Result: "hello" + [3, 3, 3] = 8 bytes

### 7.2 Unpadding

```java
static byte[] unpad(byte[] data) {
    int padding = data[data.length - 1];
    return Arrays.copyOf(data, data.length - padding);
}
```

**Logic:**

- Read last byte to know padding amount
- Remove that many bytes from end

**Example:** [h, e, l, l, o, 3, 3, 3]

- Last byte = 3 → remove 3 bytes
- Result: [h, e, l, l, o]

---

## 8. PUBLIC API SECTION

### 8.1 Encrypt Plaintext String

```java
public static String encryptText(String plaintext, String keyText) {
    byte[] data = pad(plaintext.getBytes());
    byte[] keyBytes = Arrays.copyOf(keyText.getBytes(), 8);
    long[] keys = generateKeys(keyBytes);
```

- Pad plaintext to multiple of 8 bytes
- Convert key string to first 8 bytes (truncate or pad if needed)
- Generate 16 round keys

```java
    StringBuilder hex = new StringBuilder();
    for (int i = 0; i < data.length; i += 8) {
        long block = 0;
        for (int j = 0; j < 8; j++) {
            block = (block << 8) | (data[i + j] & 0xFF);
        }
```

- Process each 8-byte block
- Convert 8 bytes to 64-bit long:
  - Shift previous value left 8 bits
  - Add next byte

```java
        long encrypted = encryptBlock(block, keys, true);
        hex.append(String.format("%016X", encrypted));
    }
    return hex.toString();
}
```

- Encrypt each 64-bit block
- Convert to hexadecimal (16 characters, 64 bits ÷ 4 bits per hex digit)
- Concatenate all blocks

### 8.2 Decrypt Hexadecimal Ciphertext

```java
public static String decryptText(String cipherHex, String keyText) {
    byte[] keyBytes = Arrays.copyOf(keyText.getBytes(), 8);
    long[] keys = generateKeys(keyBytes);
```

- Same key generation as encryption

```java
    byte[] output = new byte[cipherHex.length() / 2];
    for (int i = 0; i < cipherHex.length(); i += 16) {
        long block = Long.parseUnsignedLong(cipherHex.substring(i, i + 16), 16);
```

- Allocate output array (2 hex chars = 1 byte)
- Process each 16-character hex block (64 bits)
- Convert hex string to 64-bit long

```java
        long decrypted = encryptBlock(block, keys, false);

        for (int j = 7; j >= 0; j--) {
            output[(i / 2) + (7 - j)] = (byte) ((decrypted >>> (8 * j)) & 0xFF);
        }
    }
    return new String(unpad(output));
}
```

- Decrypt block using `encryptBlock(..., false)` (reverse key order)
- Convert 64-bit result back to 8 bytes:
  - Extract each byte from high to low
  - `decrypted >>> (8 * j)` shifts to get desired byte at position 0
  - `& 0xFF` masks to get only 8 bits
- Remove PKCS#5 padding and convert to string

---

## 9. MAIN METHOD (DEMO)

```java
public static void main(String[] args) {
    String plaintext = "helloworld";
    String key = "mysecret";

    System.out.println("Plaintext : " + plaintext);

    String cipher = encryptText(plaintext, key);
    System.out.println("Ciphertext (Hex): " + cipher);

    String decrypted = decryptText(cipher, key);
    System.out.println("Decrypted : " + decrypted);
}
```

**Demonstration:**

1. Define plaintext and key
2. Encrypt plaintext to hexadecimal ciphertext
3. Decrypt ciphertext back to plaintext
4. Verify round-trip works

---

## Key Algorithm Flow Summary

```
ENCRYPTION:
Plaintext → [Pad] → [Split into 64-bit blocks] →
[IP permutation] → [16 Feistel rounds with key schedule] →
[FP permutation] → Ciphertext (Hex)

DECRYPTION:
Ciphertext (Hex) → [Split into 64-bit blocks] →
[IP permutation] → [16 Feistel rounds with reversed keys] →
[FP permutation] → [Unpad] → Plaintext
```

---

## Important DES Characteristics

| Feature            | Detail                                                    |
| ------------------ | --------------------------------------------------------- |
| **Block Size**     | 64 bits                                                   |
| **Key Size**       | 56 bits (64 bits with parity)                             |
| **Rounds**         | 16                                                        |
| **Round Key Size** | 48 bits                                                   |
| **Non-linearity**  | S-Boxes (main source of security)                         |
| **Reversibility**  | Same algorithm for encrypt/decrypt by reversing key order |
| **Padding**        | PKCS#5 (1-8 bytes of value = padding amount)              |
