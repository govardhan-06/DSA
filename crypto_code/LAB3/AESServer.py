#!/usr/bin/env python3
"""
AES Server - Receives encrypted data and decrypts it
Port: 8060
"""

import socket
from AES import decrypt

HOST = '127.0.0.1'
PORT = 8060

# Create TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((HOST, PORT))

# Listen for incoming connections
server_socket.listen(1)
print(f"AES Server is listening on {HOST}:{PORT}...")

# Accept client connection
conn, addr = server_socket.accept()
print(f"\nConnected by {addr}\n")

try:
    # Receive ciphertext from client
    ciphertext = conn.recv(1024).decode().strip()
    print(f"========== RECEIVED FROM CLIENT ==========")
    print(f"Received Ciphertext: {ciphertext}\n")
    
    # Get key from user
    key_str = input("Enter 16-character Key for Decryption: ").strip()
    
    # Pad or truncate key to 16 characters
    key_str = (key_str + "0" * 16)[:16]
    print(f"Key: {key_str}\n")
    
    # Decrypt
    print("========== AES-128 DECRYPTION AT SERVER ==========")
    decrypted = decrypt(ciphertext, key_str)
    
    # Convert hex to ASCII using built-in bytes.fromhex()
    decrypted_ascii = bytes.fromhex(decrypted.replace(" ", "").replace("\n", "")).decode('utf-8', errors='replace')
    
    print(f"\n========== DECRYPTION RESULT ==========")
    print(f"Decrypted Plaintext (ASCII): {decrypted_ascii}")
    print(f"Decrypted Plaintext (Hex): {decrypted}\n")
    
    # Send result back to client
    conn.sendall(decrypted_ascii.encode())
    print(f"Sent decrypted plaintext back to client.")
    
except Exception as e:
    print(f"Error: {e}")
finally:
    conn.close()
    server_socket.close()
    print("\nServer closed.")
