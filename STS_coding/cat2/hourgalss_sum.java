import java.util.Scanner;

public class Hourglass {

    // Function to find the maximum hourglass sum
    static int findMaxSum(int[][] mat, int R, int C) {
        if (R < 3 || C < 3) {
            System.out.println("Not possible: matrix too small for an hourglass.");
            System.exit(0);
        }

        int max_sum = Integer.MIN_VALUE; // Use MIN_VALUE to handle negative numbers
        int sum;

        // Iterate over all possible hourglass starting points
        for (int i = 0; i < R - 2; i++) {
            for (int j = 0; j < C - 2; j++) {
                sum = mat[i][j] + mat[i][j + 1] + mat[i][j + 2]   // Top row
                    + mat[i + 1][j + 1]                            // Middle element
                    + mat[i + 2][j] + mat[i + 2][j + 1] + mat[i + 2][j + 2]; // Bottom row

                max_sum = Math.max(max_sum, sum);
            }
        }
        return max_sum;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter number of rows and columns:");
        int R = sc.nextInt();
        int C = sc.nextInt();

        int[][] mat = new int[R][C];
        System.out.println("Enter matrix elements:");
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                mat[i][j] = sc.nextInt();
            }
        }

        int res = findMaxSum(mat, R, C);
        System.out.println("Maximum sum of hourglass = " + res);

        sc.close();
    }
}
