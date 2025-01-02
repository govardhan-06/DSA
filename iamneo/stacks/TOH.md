# Tower of Wisdom Ritual Solver

## Question Overview

During an archaeological expedition, a team discovers the "Disk of Light," an ancient artifact composed of concentric rings, each inscribed with unique symbols. To unlock the secrets and powers of this artifact, they must perform the ancient "Tower of Wisdom" ritual. This ritual follows specific rules regarding the movement of disks between pedestals.

This program assists the archaeological team by calculating the sequence of moves required to solve the Tower of Wisdom puzzle and the total number of disk moves involved.

## Problem Description

The Tower of Wisdom ritual is performed using:

- **Three pedestals**: Source (A), Auxiliary (B), and Illuminated (C).
- **A stack of disks**: Each disk is of different size, with smaller disks placed on top of larger ones on the Source pedestal.

### Rules:

1. Only **one disk** can be moved at a time.
2. A disk can only be placed on top of a **larger disk** or on an **empty pedestal**.

Your task is to display the sequence of moves required to move all the disks from the **Source pedestal (A)** to the **Illuminated pedestal (C)**, following the above rules, and output the total number of moves.

## Input Format

- The input consists of a single integer `n` denoting the number of disks.
  - **Constraints**: 1 ≤ n ≤ 8

## Output Format

- The output displays the exact sequence of moves required to solve the puzzle.
- The final output line shows the **total number of moves**.

### Example

#### Input 1:

```
3
```

#### Output 1:

```
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Total number of times the disk is moved: 7
```

## Code Constraints:

- The number of disks, `n`, is between **1** and **8** (inclusive).

## How It Works:

The solution is based on the classic **Tower of Hanoi** puzzle, where the program recursively moves disks between pedestals while adhering to the defined rules. The total number of moves required is always `2^n - 1` for `n` disks.
