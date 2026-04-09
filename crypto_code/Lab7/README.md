Lab7 contains three separate client/server demos: SHA-512 hashing, MD5 hashing, and DSS signature generation/verification. In each demo, the server starts first and waits on a port, then the matching client connects and sends data.

1. DSSServer.java and DSSClient.java implement a DSS-style signing and verification flow. The client reads p, q, g, builds a simple hash of the transaction, generates a private key, public key, and signature, then sends everything to the server. The server receives the values, recomputes the verification value, and checks whether the signature is valid.
2. DSSAttackerClient.java is an alternate client for the same DSS server. It sends random fake signature values to show what an invalid or tampered transaction looks like.
3. MD5Server.java and MD5Client.java implement a hash-verification demo using Java’s built-in MD5. The client hashes the message and sends both the message and hash; the server recomputes the MD5 and compares the two hashes.
4. SHAServer.java and SHAClient.java implement a hash-verification demo using Java’s built-in SHA-512. The client hashes the message and sends both the message and hash; the server recomputes the SHA-512 hash and compares the two hashes.

Hash comparison:

- SHA-512 is far stronger than MD5 for security because it produces a 512-bit digest and is considered collision-resistant for practical use.
- MD5 is fast but broken for collision resistance, so it should not be used for security-sensitive signatures or integrity checks.
- DSS should use a secure hash such as SHA-512 rather than MD5 or a toy checksum, which is why the DSS code now hashes the message with SHA-512.

Execution order for each demo is:

1. Start the server.
2. Run the matching client.
3. For the DSS demo, you can run either DSSClient.java for a valid signature or DSSAttackerClient.java for an invalid one.

So the practical order is:

- SHAServer.java → SHAClient.java
- MD5Server.java → MD5Client.java
- DSSServer.java → DSSClient.java or DSSAttackerClient.java
