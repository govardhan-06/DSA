import java.util.*;

class Main {

    static boolean check(int ip[], int op[], int n) {
        Stack<Integer> stack = new Stack<>();
        int j = 0; // pointer for output array

        for (int i = 0; i < n; i++) {
            // push current input element
            stack.push(ip[i]);

            // pop while top matches output element
            while (!stack.isEmpty() && j < n && stack.peek() == op[j]) {
                stack.pop();
                j++;
            }
        }

        // if stack is empty, permutation is valid
        return stack.isEmpty();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        int input[] = new int[n];
        int output[] = new int[n];

        for (int i = 0; i < n; i++)
            input[i] = sc.nextInt();

        for (int i = 0; i < n; i++)
            output[i] = sc.nextInt();

        if (check(input, output, n))
            System.out.println("Yes");
        else
            System.out.println("Not Possible");

        sc.close();
    }
}
