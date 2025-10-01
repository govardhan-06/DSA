public class MES {

    // Function to find the maximum equilibrium sum
    public static int getMaxEquilibriumSumOptimized(int[] arr) {
        int totalSum = 0;
        int leftSum = 0;
        int maxSum = Integer.MIN_VALUE;

        // Step 1: Calculate total sum of the array
        for (int i = 0; i < arr.length; i++) {
            totalSum += arr[i];
        }

        // Step 2: Iterate through array to find equilibrium sums
        for (int i = 0; i < arr.length; i++) {
            totalSum -= arr[i]; // Right sum for current index

            if (leftSum == totalSum && leftSum > maxSum) {
                maxSum = leftSum;
            }

            leftSum += arr[i]; // Update left sum for next index
        }

        return maxSum;
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5, 4, 3, 2, 1};
        int maxSum = getMaxEquilibriumSumOptimized(arr);
        System.out.println("Max Equilibrium Sum : " + maxSum);
    }
}
