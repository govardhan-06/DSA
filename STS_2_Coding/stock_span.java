import java.util.*;

/*
Input:
6
97 64 32 11 22 56
Output:
[1, 1, 1, 1, 2, 4]
*/

public class Main {

    static void calculateSpan(int arr[], int n, int span[]) {
        Stack<Integer> st = new Stack<>();

        // First day span is always 1
        st.push(0);
        span[0] = 1;

        // Calculate span for remaining days
        for (int i = 1; i < n; i++) {

            // Pop elements while stack top price <= current price
            while (!st.isEmpty() && arr[st.peek()] <= arr[i]) {
                st.pop();
            }

            // If stack empty, span is i+1
            // Else span is distance from last greater element
            span[i] = st.isEmpty() ? (i + 1) : (i - st.peek());

            // Push current index
            st.push(i);
        }
    }

    static void printArray(int arr[]) {
        System.out.println(Arrays.toString(arr));
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int arr[] = new int[n];

        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        int span[] = new int[n];

        calculateSpan(arr, n, span);
        printArray(span);

        sc.close();
    }
}