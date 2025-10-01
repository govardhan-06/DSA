import java.util.Scanner;

public class MajorityElement {

    // Function to find majority element
    public static int findMajorityElement(int[] nums) {
        int candidate = 0;
        int count = 0;

        // Step 1: Find a potential candidate
        for (int num : nums) {
            if (count == 0) {
                candidate = num;
                count = 1;
            } else if (candidate == num) {
                count++;
            } else {
                count--;
            }
        }

        // Step 2: Verify the candidate
        int majorityCount = 0;
        for (int num : nums) {
            if (num == candidate) {
                majorityCount++;
            }
        }

        if (majorityCount > nums.length / 2) {
            return candidate;
        }

        return -1; // No majority element found
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the size of the array:");
        int n = sc.nextInt();
        int[] nums = new int[n];

        System.out.println("Enter the elements of the array:");
        for (int i = 0; i < n; i++) {
            nums[i] = sc.nextInt();
        }

        int majorityElement = findMajorityElement(nums);

        if (majorityElement != -1) {
            System.out.println("Majority element: " + majorityElement);
        } else {
            System.out.println("No majority element found.");
        }

        sc.close();
    }
}
