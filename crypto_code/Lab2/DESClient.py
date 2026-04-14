#!/usr/bin/env python3
"""
DES Client - Encrypts plaintext and sends it to server
Server: localhost:8050
"""

import socket
from DES import encrypt_text

HOST = '127.0.0.1'
PORT = 8050

print("========== DES CLIENT ==========\n")

# Get user input
key = input("Enter Key (any string, first 8 chars will be used): ").strip()
if not key:
    key = "mysecret"
    print(f"Using default key: {key}")

plaintext = input("Enter Plaintext: ").strip()
if not plaintext:
    plaintext = "helloworld"
    print(f"Using default plaintext: {plaintext}")

# Encrypt the plaintext
print("\n========== DES ENCRYPTION ==========\n")
print(f"Plaintext: {plaintext}")
print(f"Key: {key}")
print()

ciphertext = encrypt_text(plaintext, key)
print(f"\nCiphertext (Hex): {ciphertext}\n")

# Connect to server
print("========== SENDING TO SERVER ==========")

try:
    # Create TCP socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((HOST, PORT))
    
    # Send key to server
    client_socket.sendall(key.encode())
    print(f"Sent key: {key}")
    
    # Send ciphertext to server
    client_socket.sendall(ciphertext.encode())
    print(f"Sent ciphertext: {ciphertext}")
    
    # Receive decrypted plaintext from server
    response = client_socket.recv(1024).decode()
    print(f"\nServer says: {response}\n")
    
    client_socket.close()
    
except ConnectionRefusedError:
    print(f"Error: Could not connect to server on {HOST}:{PORT}")
    print("Please make sure DESServer.py is running.")
except Exception as e:
    print(f"Error: {e}")
