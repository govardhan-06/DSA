"""
AES-128 Implementation in Python with Intermediate Steps
-------------------------------------------------------
Features:
1. Manual AES-128 implementation (no crypto libraries).
2. Includes Key Expansion, SubBytes, ShiftRows, MixColumns, and AddRoundKey.
3. Prints intermediate states for each encryption and decryption round.
4. Suitable for academic and lab exam purposes.
"""

# ===================== CONSTANTS ===================== #

ROUNDS = 10

# AES S-Box
SBOX = [
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
]

# Build inverse S-Box
RSBOX = [0] * 256
for i in range(256):
    RSBOX[SBOX[i]] = i

# Round constants
RCON = [0x00, 0x01, 0x02, 0x04, 0x08, 0x10,
        0x20, 0x40, 0x80, 0x1B, 0x36]

# ===================== UTILITY FUNCTIONS ===================== #

def print_state(msg, state):
    """Print the AES state as a 4x4 matrix."""
    print(msg)
    for i in range(4):
        for j in range(4):
            print(f"{state[i*4 + j]:02X}", end=" ")
        print()
    print()

def galois_mul(a, b):
    """Multiply two bytes in GF(2^8)."""
    p = 0
    for _ in range(8):
        if b & 1:        # If the least significant bit of b is 1
            p ^= a       # Add 'a' to the product (XOR in GF arithmetic)
        hi_bit = a & 0x80  # Check if the MSB of 'a' is set
        a = (a << 1) & 0xFF  # Left shift 'a' (multiply by x) and keep 8 bits
        if hi_bit:       # If overflow occurs
            a ^= 0x1B    # Reduce using AES polynomial
        b >>= 1          # Move to the next bit of 'b'
    return p

# ===================== AES TRANSFORMATIONS ===================== #

def add_round_key(state, key):
    for i in range(16):
        state[i] ^= key[i]

def sub_bytes(state):
    for i in range(16):
        state[i] = SBOX[state[i]]

def inv_sub_bytes(state):
    for i in range(16):
        state[i] = RSBOX[state[i]]

# STATE REPRESENTATIONS:
# | 0   4   8  12 |
# | 1   5   9  13 |
# | 2   6  10  14 |
# | 3   7  11  15 |

# | Row   | Shift     |
# | ----- | --------- |
# | Row 0 | No shift  |
# | Row 1 | Left by 1 |
# | Row 2 | Left by 2 |
# | Row 3 | Left by 3 |

def shift_rows(state):
    temp = state.copy()
    state[1], state[5], state[9], state[13] = temp[5], temp[9], temp[13], temp[1]
    state[2], state[6], state[10], state[14] = temp[10], temp[14], temp[2], temp[6]
    state[3], state[7], state[11], state[15] = temp[15], temp[3], temp[7], temp[11]

def inv_shift_rows(state):
    temp = state.copy()
    state[5], state[9], state[13], state[1] = temp[1], temp[5], temp[9], temp[13]
    state[10], state[14], state[2], state[6] = temp[2], temp[6], temp[10], temp[14]
    state[15], state[3], state[7], state[11] = temp[3], temp[7], temp[11], temp[15]

# 2 3 1 1
# 1 2 3 1
# 1 1 2 3
# 3 1 1 2

def mix_columns(state):
    for i in range(4):
        a, b, c, d = state[i*4:(i+1)*4]
        state[i*4 + 0] = galois_mul(a, 2) ^ galois_mul(b, 3) ^ c ^ d
        state[i*4 + 1] = a ^ galois_mul(b, 2) ^ galois_mul(c, 3) ^ d
        state[i*4 + 2] = a ^ b ^ galois_mul(c, 2) ^ galois_mul(d, 3)
        state[i*4 + 3] = galois_mul(a, 3) ^ b ^ c ^ galois_mul(d, 2)

# 0E 0B 0D 09
# 0B 0D 09 0E
# 0D 09 0E 0B
# 09 0E 0B 0D

def inv_mix_columns(state):
    for i in range(4):
        a, b, c, d = state[i*4:(i+1)*4]
        state[i*4 + 0] = galois_mul(a, 0x0E) ^ galois_mul(b, 0x0B) ^ galois_mul(c, 0x0D) ^ galois_mul(d, 0x09)
        state[i*4 + 1] = galois_mul(a, 0x09) ^ galois_mul(b, 0x0E) ^ galois_mul(c, 0x0B) ^ galois_mul(d, 0x0D)
        state[i*4 + 2] = galois_mul(a, 0x0D) ^ galois_mul(b, 0x09) ^ galois_mul(c, 0x0E) ^ galois_mul(d, 0x0B)
        state[i*4 + 3] = galois_mul(a, 0x0B) ^ galois_mul(b, 0x0D) ^ galois_mul(c, 0x09) ^ galois_mul(d, 0x0E)

# ===================== KEY EXPANSION ===================== #

def key_expansion(key):
    """
    AES-128 Key Expansion (Key Schedule)

    This function generates 11 round keys from the original 16-byte key.
    - AES-128 uses 10 rounds, plus an initial AddRoundKey step.
    - Therefore, 11 round keys (K0 to K10) are required.
    - Each round key is 16 bytes (128 bits).

    Parameters:
        key (list or bytes): A 16-byte (128-bit) encryption key.

    Returns:
        round_keys (list): A list of 11 round keys, each containing 16 bytes.
    """

    # The first round key (K0) is simply the original key.
    # Convert the key into a list to allow byte-wise manipulation.
    round_keys = [list(key)]

    # Generate the remaining 10 round keys (K1 to K10)
    for i in range(1, 11):
        # 'prev' holds the previous round key (Ki-1)
        prev = round_keys[i - 1]

        # Step 1: Extract the last 4 bytes (one 32-bit word) of the previous key.
        last_word = prev[12:16]

        # Step 2: RotWord
        # Perform a cyclic left shift on the 4-byte word.
        last_word = last_word[1:] + last_word[:1]

        # Step 3: SubWord
        # Apply the AES S-Box substitution to each byte of the rotated word.
        last_word = [SBOX[b] for b in last_word]

        # Step 4: Rcon (Round Constant) Addition
        # XOR the first byte of the transformed word with the round constant.
        # RCON ensures that each round key is unique and prevents symmetry.
        last_word[0] ^= RCON[i]

        # Step 5: Generate the First Word of the New Round Key
        # The first 4 bytes of the new key are obtained by XORing the
        # transformed word with the first 4 bytes of the previous key.
        new_key = [prev[j] ^ last_word[j] for j in range(4)]

        # Step 6: Generate the Remaining Words
        # Each subsequent word is generated by XORing the corresponding
        # word of the previous key with the word generated 4 bytes earlier.
        # This creates a chain dependency across the entire key.
        # Formula:
        #   W[i] = W[i-4] XOR W[i-1]
        # where W represents 4-byte words.
        for j in range(4, 16):
            new_key.append(prev[j] ^ new_key[j - 4])

        # Append the newly generated round key to the list.
        round_keys.append(new_key)

    # Return the complete list of 11 round keys (K0 to K10).
    return round_keys

# ===================== ENCRYPTION ===================== #

def encrypt(plaintext, key_str):
    # Normalize plaintext to 16 bytes
    plaintext = (plaintext + "X" * 16)[:16]
    state = list(plaintext.encode())

    # Normalize key to 16 bytes
    key = list((key_str + "\0" * 16)[:16].encode())
    round_keys = key_expansion(key)

    print_state("Initial Plaintext State:", state)

    add_round_key(state, round_keys[0])
    print_state("After Initial AddRoundKey (Round 0):", state)

    for round_num in range(1, 10):
        print(f"========== ROUND {round_num} ==========")
        sub_bytes(state)
        print_state("After SubBytes:", state)

        shift_rows(state)
        print_state("After ShiftRows:", state)

        mix_columns(state)
        print_state("After MixColumns:", state)

        add_round_key(state, round_keys[round_num])
        print_state(f"After AddRoundKey (Round {round_num}):", state)

    print("========== FINAL ROUND (10) ==========")
    sub_bytes(state)
    print_state("After SubBytes:", state)

    shift_rows(state)
    print_state("After ShiftRows:", state)

    add_round_key(state, round_keys[10])
    print_state("After Final AddRoundKey:", state)

    cipher_hex = ''.join(f"{b:02X}" for b in state)
    print("Final Ciphertext:", cipher_hex)
    print()
    return cipher_hex

# ===================== DECRYPTION ===================== #

def decrypt(cipher_hex, key_str):
    state = list(bytes.fromhex(cipher_hex))
    key = list((key_str + "\0" * 16)[:16].encode())
    round_keys = key_expansion(key)

    print_state("Initial Ciphertext State:", state)

    add_round_key(state, round_keys[10])
    print_state("After Initial AddRoundKey (Round 10):", state)

    for round_num in range(9, 0, -1):
        print(f"========== INVERSE ROUND {round_num} ==========")
        inv_shift_rows(state)
        print_state("After InvShiftRows:", state)

        inv_sub_bytes(state)
        print_state("After InvSubBytes:", state)

        add_round_key(state, round_keys[round_num])
        print_state(f"After AddRoundKey (Round {round_num}):", state)

        inv_mix_columns(state)
        print_state("After InvMixColumns:", state)

    print("========== FINAL STEP ==========")
    inv_shift_rows(state)
    print_state("After FinalRound InvShiftRows:", state)

    inv_sub_bytes(state)
    print_state("After FinalRound InvSubBytes:", state)

    add_round_key(state, round_keys[0])
    print_state("After Final AddRoundKey (Round 0):", state)

    plaintext = bytes(state).decode(errors='ignore')
    print("Final Decrypted Text:", plaintext)
    print()
    return plaintext

# ===================== MAIN ===================== #

if __name__ == "__main__":
    plaintext = "HELLOWORLD12345"
    key = "mysecretkey1234"

    cipher = encrypt(plaintext, key)
    decrypted = decrypt(cipher, key)