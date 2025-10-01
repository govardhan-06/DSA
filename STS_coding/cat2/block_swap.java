import java.util.Scanner;

public class BlockSwapAlgorithm {

    // Function to left rotate arr[] by d positions
    public static void leftRotate(int arr[], int d, int n) {
        if (d == 0 || d == n) return;  // No rotation needed
        if (d > n) d = d % n;          // Normalize if d > n

        int i = d;       // Size of block A
        int j = n - d;   // Size of block B

        // Recursively swap blocks
        while (i != j) {
            if (i < j) {            // A is shorter
                swap(arr, d - i, d + j - i, i);
                j -= i;
            } else {                // B is shorter
                swap(arr, d - i, d, j);
                i -= j;
            }
        }
        // Swap remaining equal-size blocks
        swap(arr, d - i, d, i);
    }

    // Utility function to swap d elements starting at fi with si
    public static void swap(int arr[], int fi, int si, int d) {
        for (int k = 0; k < d; k++) {
            int temp = arr[fi + k];
            arr[fi + k] = arr[si + k];
            arr[si + k] = temp;
        }
    }

    // Utility function to print an array
    public static void printArray(int arr[], int size) {
        for (int i = 0; i < size; i++)
            System.out.print(arr[i] + " ");
        System.out.println();
    }

    // Main function to test the algorithm
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter size of the array:");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.println("Enter array elements:");
        for (int i = 0; i < n; i++)
            arr[i] = sc.nextInt();

        System.out.println("Enter number of rotations:");
        int d = sc.nextInt();

        leftRotate(arr, d, n);

        System.out.println("Rotated array:");
        printArray(arr, n);

        sc.close();
    }
}
