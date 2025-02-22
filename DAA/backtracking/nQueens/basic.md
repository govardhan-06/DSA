### **Time Complexity Analysis**

The given approach is a **backtracking** solution to the N-Queens problem. The function recursively explores valid placements column by column, using `isSafe()` to check whether a queen can be placed in a given row and column.

#### **1. Recursive Calls (Backtracking)**

- For each column, the algorithm iterates over all \( N \) rows and calls `isSafe()` for each row.
- If a valid row is found, it places a queen and moves to the next column recursively.
- The worst-case recurrence follows:
  \[
  T(n) = N \cdot T(n-1)
  \]
  Expanding this:
  \[
  T(n) = N \cdot (N-1) \cdot (N-2) \cdots 1 = O(N!)
  \]
  - This means the worst-case time complexity is **\( O(N!) \)**.

#### **2. Checking for Safety (`isSafe()`)**

- The `isSafe()` function checks:
  - The **upper diagonal** → At most \( O(N) \) operations.
  - The **same row** (leftward) → At most \( O(N) \) operations.
  - The **lower diagonal** → At most \( O(N) \) operations.
- Each call to `isSafe()` takes **\( O(N) \)** in the worst case.

#### **Total Time Complexity**

- Since `isSafe()` is called for each recursive state and takes **\( O(N) \)** time per call:
  - There are approximately **\( O(N!) \)** recursive calls.
  - Each call executes `isSafe()` in **\( O(N) \)** time.
- Therefore, the total time complexity is:
  \[
  O(N! \cdot N)
  \]
  - This is slightly worse than **\( O(N!) \)** but still asymptotically dominated by **\( O(N!) \)**.

### **Space Complexity Analysis**

1. **Board Representation:**

   - The `board` is stored as a **vector of strings** of size \( N \times N \) → **\( O(N^2) \)**.

2. **Recursive Call Stack:**

   - Since there are at most **\( O(N) \)** recursive calls (one for each column in the worst case), the recursion depth is **\( O(N) \)**.

3. **Auxiliary Space (Vectors & Strings):**
   - The **`ans` vector** stores all valid solutions, which can take up additional space depending on the number of valid configurations.
   - The worst case number of valid solutions is **exponential** in \( N \), leading to additional space usage.

#### **Total Space Complexity**

- **Explicit space**: \( O(N^2) \) (for the board).
- **Recursive space**: \( O(N) \) (due to recursion depth).
- **Final complexity**:  
  \[
  O(N^2) \text{ (for board)} + O(N) \text{ (for recursion)} = O(N^2)
  \]
  (excluding the storage for the final answer).

### **Final Complexity Summary**

| Aspect               | Complexity          |
| -------------------- | ------------------- |
| **Time Complexity**  | \( O(N! \cdot N) \) |
| **Space Complexity** | \( O(N^2) \)        |

#### **Comparison with Optimized Approach (Bitmasking or Hashing)**

- The previous solution using **hash tables (`leftRow`, `upperDiagonal`, `lowerDiagonal`)** had an optimized **`O(N!)`** time complexity, as `isSafe()` was replaced with **constant-time lookups**.
- This implementation, however, has an extra **\( O(N) \)** factor due to `isSafe()`, making it **slower** in practice.

For larger \( N \), the hash-based solution is preferable.
