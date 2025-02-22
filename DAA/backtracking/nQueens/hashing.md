### **Time Complexity Analysis**

The N-Queens problem involves placing \( N \) queens on an \( N \times N \) chessboard such that no two queens attack each other. This backtracking approach tries all possible placements column by column.

1. **Recursive Calls:**

   - In the worst case, for each column, we attempt to place a queen in one of \( N \) rows.
   - If a queen is placed, a recursive call is made for the next column.
   - This process continues until either a valid configuration is found or all possibilities are exhausted.

2. **Branching Factor:**

   - At each column, there are at most \( N \) choices (rows) for placing a queen.
   - The number of recursive calls follows an approximate recurrence:  
     \[
     T(n) = N \cdot T(n-1)
     \]
   - Expanding this gives:
     \[
     T(n) = N \cdot (N-1) \cdot (N-2) \cdots 1 = O(N!)
     \]

3. **Pruning with Hashing:**
   - The use of three hash tables (**leftRow, upperDiagonal, lowerDiagonal**) reduces unnecessary recursive calls by ensuring invalid positions are skipped.
   - Despite pruning, the worst-case complexity remains **\( O(N!) \)**, as we are still trying all valid placements.

### **Space Complexity Analysis**

1. **Auxiliary Space:**

   - **Board Representation:** A vector of strings of size \( N \times N \) → \( O(N^2) \).
   - **Hashing Structures:**
     - **leftRow:** Stores \( N \) values → \( O(N) \).
     - **upperDiagonal:** Stores \( 2N-1 \) values → \( O(N) \).
     - **lowerDiagonal:** Stores \( 2N-1 \) values → \( O(N) \).
     - Total storage for hashing structures → \( O(N) + O(N) + O(N) = O(N) \).

2. **Recursive Call Stack:**
   - At worst, the recursion depth reaches \( O(N) \) (one function call per column).
   - Each call has constant space overhead → Total **\( O(N) \)**.

### **Final Complexity:**

- **Time Complexity:** \( O(N!) \)
- **Space Complexity:** \( O(N^2) \) (for board) + \( O(N) \) (for hashing + recursion)  
  → **Overall \( O(N^2) \)** due to the board representation.
