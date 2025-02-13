The **0/1 Knapsack Problem** is a classic optimization problem in computer science and dynamic programming. Here's how it works:

---

### Problem Statement:

You have:

- A **knapsack** with a maximum weight capacity \( W \).
- **N items**, each with:
  - A weight \( w_i \)
  - A value \( v_i \)

Your goal is to maximize the total value of items in the knapsack without exceeding its weight capacity.

### Constraints:

1. You **cannot** take a fractional part of an item — it's either **included (1)** or **not included (0)**, hence the name **0/1 Knapsack**.
2. Each item can be selected at most once.

---

### Example:

Consider the following items:

| Item | Weight | Value |
| ---- | ------ | ----- |
| 1    | 2      | 3     |
| 2    | 3      | 4     |
| 3    | 4      | 5     |
| 4    | 5      | 6     |

**Knapsack Capacity** \( W = 5 \)

- If you choose items 1 and 2:
  - Total weight = \( 2 + 3 = 5 \) (fits in the knapsack)
  - Total value = \( 3 + 4 = 7 \)
- If you choose item 3:
  - Total weight = \( 4 \) (fits)
  - Total value = \( 5 \)
- If you choose item 4:
  - Total weight = \( 5 \) (fits)
  - Total value = \( 6 \)

The **optimal solution** is to take items **1 and 2**, giving a maximum value of **7**.

---

### Dynamic Programming Approach:

We use a **2D DP table** where:

- \( dp[i][w] \) represents the maximum value that can be attained with the first \( i \) items and a maximum weight capacity of \( w \).

---

### Recurrence Relation:

For each item \( i \):

- **If you don’t take the item**: The value is the same as not having that item:
  \[
  dp[i][w] = dp[i-1][w]
  \]
- **If you take the item**: Add its value and subtract its weight from the capacity:
  \[
  dp[i][w] = v_i + dp[i-1][w - w_i]
  \]
- **Choose the maximum** of the above two:
  \[
  dp[i][w] = \max(dp[i-1][w], v_i + dp[i-1][w - w_i])
  \]

---

### Algorithm:

1. **Initialize a 2D DP array** with dimensions \( (N+1) \times (W+1) \), initialized to 0.
2. **Iterate over all items** and all capacities:
   - If the current item's weight is less than or equal to the current capacity, calculate the maximum value by including or excluding the item.
   - Otherwise, exclude the item.
3. **Return** the value at \( dp[N][W] \), which is the maximum value achievable.

---

### Code Implementation:

Here's a simple implementation in **Java**:

```java
public class Knapsack {
    public static int knapSack(int W, int[] weights, int[] values, int n) {
        int[][] dp = new int[n + 1][W + 1];

        // Build table dp[][] in bottom-up manner
        for (int i = 0; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                if (i == 0 || w == 0) {
                    dp[i][w] = 0;
                } else if (weights[i - 1] <= w) {
                    dp[i][w] = Math.max(values[i - 1] + dp[i - 1][w - weights[i - 1]],
                                        dp[i - 1][w]);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        return dp[n][W];
    }

    public static void main(String[] args) {
        int[] values = {3, 4, 5, 6};
        int[] weights = {2, 3, 4, 5};
        int W = 5;
        int n = values.length;

        System.out.println("Maximum value: " + knapSack(W, weights, values, n));
    }
}
```

---

### Complexity:

- **Time Complexity**: \( O(N \times W) \) — Nested loops over items and capacities.
- **Space Complexity**: \( O(N \times W) \) — For the DP table.

---

### Key Takeaways:

- It's called **0/1** because each item can either be taken **(1)** or left behind **(0)**.
- Dynamic Programming efficiently solves it with a **bottom-up approach**.
- The solution finds the **maximum value** without exceeding the knapsack's weight capacity.

If you have any questions about this or need help with variations (like the **Fractional Knapsack Problem**), let me know!
