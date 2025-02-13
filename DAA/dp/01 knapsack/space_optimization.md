# Space Optimization Strategy

## Idea:

- Use a **1D array (`prev`)** instead of a 2D table.
- `prev[W]` represents the maximum value for weight **W** using items considered so far.

## How It Works:

### 1. Initialize `prev`:

- **Base case:** When considering only the first item (`ind = 0`), fill the array based on its value.
  - If the item's weight is less than or equal to the capacity, take it.

### 2. Iterate through items:

- Start from the **second item (`ind = 1`)** and go to the last.
- For each weight capacity (`W`), decide whether to take or not take the current item:
  - **Not Take:** Use the value from the previous state:
    ```plaintext
    notTake = prev[W]
    ```
  - **Take:** Include the current item if it fits:
    ```plaintext
    take = val[ind] + prev[W - wt[ind]]
    ```
  - **Choose the maximum** of the two options:
    ```plaintext
    prev[W] = max(take, notTake)
    ```

### 3. Reverse Loop for Weight:

- **Looping backwards** (`W = maxWeight → 0`) is crucial because:
  - If we go forward, the current state would overwrite values needed for the next calculation.
  - Going backward ensures we're always using values from the previous state.
