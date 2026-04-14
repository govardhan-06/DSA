#!/usr/bin/env python3
"""
DES Server - Receives encrypted data and decrypts it
Port: 8050
"""

import socket
from DES import decrypt_text

HOST = '127.0.0.1'
PORT = 8050

# Create TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((HOST, PORT))

# Listen for incoming connections
server_socket.listen(1)
print(f"DES Server is listening on {HOST}:{PORT}...")

# Accept client connection
conn, addr = server_socket.accept()
print(f"\nConnected by {addr}\n")

try:
    # Receive key from client
    key = conn.recv(1024).decode().strip()
    print(f"Received Key: {key}")
    
    # Receive ciphertext from client
    ciphertext = conn.recv(1024).decode().strip()
    print(f"Received Ciphertext: {ciphertext}\n")
    
    # Decrypt
    print("========== DES DECRYPTION AT SERVER ==========")
    plaintext = decrypt_text(ciphertext, key)
    print(f"\nDecrypted Plaintext: {plaintext}\n")
    
    # Send decrypted message back to client
    conn.sendall(plaintext.encode())
    print(f"Sent decrypted plaintext back to client.")
    
except Exception as e:
    print(f"Error: {e}")
finally:
    conn.close()
    server_socket.close()
    print("\nServer closed.")
