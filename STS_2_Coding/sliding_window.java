import java.util.*;

public class Main {
    // Logic to calculate the maximums for each sliding window
    public static int[] maxsliding(int[] in, int w) {
        int[] max_left = new int[in.length];
        int[] max_right = new int[in.length];
        
        // Initial setup for the first and last elements
        max_left[0] = in[0];
        max_right[in.length - 1] = in[in.length - 1];
        
        // Build max_left and max_right arrays in a single pass
        for (int i = 1; i < in.length; i++) {
            // Traverse from left to right: reset max at block boundaries
            max_left[i] = (i % w == 0) ? in[i] : Math.max(max_left[i - 1], in[i]);
            
            // Traverse from right to left: reset max at block boundaries
            final int j = in.length - i - 1;
            max_right[j] = (j % w == 0) ? in[j] : Math.max(max_right[j + 1], in[j]);
        }
        
        // Final array to store the result
        final int[] sliding_max = new int[in.length - w + 1];
        for (int i = 0, j = 0; i + w <= in.length; i++) {
            // The max for any window is the max of max_right[i] and max_left[i + w - 1]
            sliding_max[j++] = Math.max(max_right[i], max_left[i + w - 1]);
        }
        return sliding_max;
    }

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt(); // Number of elements
        int k = sc.nextInt(); // Window size
        int a[] = new int[n];
        
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
        }
        
        int ans[] = maxsliding(a, k);
        for (int i = 0; i < ans.length; i++) {
            System.out.print(ans[i] + " ");
        }
    }
}