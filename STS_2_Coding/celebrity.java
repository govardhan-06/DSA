import java.util.*;

public class Main {

    public static int celebritySolution(int[][] mat) {
        Stack<Integer> stk = new Stack<>();

        // Step 1: Push all people into stack
        for (int i = 0; i < mat.length; i++) {
            stk.push(i);
        }

        // Step 2: Eliminate non-celebrities
        while (stk.size() > 1) {
            int col = stk.pop();
            int row = stk.pop();

            if (mat[row][col] == 1) {
                // row knows col → row cannot be celebrity
                stk.push(col);
            } else {
                // row does not know col → col cannot be celebrity
                stk.push(row);
            }
        }

        // Potential celebrity
        int x = stk.pop();

        // Step 3a: Row check (celebrity knows no one)
        for (int j = 0; j < mat.length; j++) {
            if (j == x) continue;
            if (mat[x][j] == 1) {
                return -1;
            }
        }

        // Step 3b: Column check (everyone knows celebrity)
        for (int i = 0; i < mat.length; i++) {
            if (i == x) continue;
            if (mat[i][x] == 0) {
                return -1;
            }
        }

        return x;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[][] matrix = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = sc.nextInt();
            }
        }

        int res = celebritySolution(matrix);

        if (res == -1)
            System.out.println("There is no celebrity in the party");
        else
            System.out.println(res + " is the celebrity in the party");
    }
}
