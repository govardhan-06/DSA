class Main {

    static int numberOfPaths(int m, int n) {
        // If either dimension is 1, only one path exists (straight line)
        if (m == 1 || n == 1) {
            return 1;
        }

        // Count paths from top and left cells
        return numberOfPaths(m - 1, n) + numberOfPaths(m, n - 1);
        // + numberOfPaths(m - 1, n - 1);  // Uncomment if diagonal moves allowed
    }

    public static void main(String[] args) {
        System.out.println(numberOfPaths(3, 3));  // Output: 6
    }
}
