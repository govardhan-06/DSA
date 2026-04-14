#!/usr/bin/env python3
"""
AES Client - Encrypts plaintext and sends it to server
Server: localhost:8060
"""

import socket
from AES import encrypt

HOST = '127.0.0.1'
PORT = 8060

print("========== AES CLIENT ==========\n")

# Get plaintext from user
plaintext = input("Enter Plaintext (max 16 characters): ").strip()

if not plaintext:
    plaintext = "HELLOWORLD12345"
    print(f"Using default plaintext: {plaintext}")

# Pad or truncate to 16 characters
plaintext = (plaintext + "X" * 16)[:16]

# Get key from user
key_str = input("Enter 16-character Key: ").strip()

if not key_str:
    key_str = "mysecretkey1234"
    print(f"Using default key: {key_str}")

# Pad or truncate key to 16 characters
key_str = (key_str + "\0" * 16)[:16]

print("\n========== AES-128 ENCRYPTION ==========")
print(f"\nPlaintext: {plaintext}")
print(f"Key: {key_str}\n")

# Encrypt the plaintext
ciphertext = encrypt(plaintext, key_str)

print(f"\n========== ENCRYPTION RESULT ==========")
print(f"Final Ciphertext (Hex): {ciphertext}\n")

# Send to server
print("========== SENDING TO SERVER ==========")

try:
    # Create TCP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((HOST, PORT))
    
    # Send ciphertext
    client_socket.sendall(ciphertext.encode())
    print(f"Ciphertext sent to server: {ciphertext}")
    
    # Receive decrypted plaintext from server
    response = client_socket.recv(1024).decode()
    print(f"\nServer says: {response}\n")
    
    client_socket.close()
    
except ConnectionRefusedError:
    print(f"Error: Could not connect to server on {HOST}:{PORT}")
    print("Please make sure AESServer.py is running.")
except Exception as e:
    print(f"Error: {e}")
