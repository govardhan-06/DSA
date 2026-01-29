import java.util.*;

class MinStack {

    Stack<Integer> s;        // main stack
    Stack<Integer> minStack; // stack to store minimums

    MinStack() {
        s = new Stack<>();
        minStack = new Stack<>();
    }

    // Push operation
    void push(int x) {
        s.push(x);

        if (minStack.isEmpty() || x <= minStack.peek()) {
            minStack.push(x);
        }

        System.out.println("Number Inserted: " + x);
    }

    // Pop operation
    void pop() {
        if (s.isEmpty()) {
            System.out.println("Stack is Empty");
            return;
        }

        int removed = s.pop();

        if (removed == minStack.peek()) {
            minStack.pop();
        }

        System.out.println("Removed element: " + removed);
    }

    // Peek / Top operation
    void top() {
        if (s.isEmpty()) {
            System.out.println("Stack is Empty");
            return;
        }

        System.out.println("Top most element: " + s.peek());
    }

    // Get minimum element
    void getMin() {
        if (minStack.isEmpty()) {
            System.out.println("Stack is Empty");
            return;
        }

        System.out.println("Minimum element: " + minStack.peek());
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        MinStack ms = new MinStack();

        int n = sc.nextInt();

        for (int i = 0; i < n; i++) {
            int x = sc.nextInt();
            ms.push(x);
        }

        ms.getMin();
        ms.pop();
        ms.getMin();
        ms.pop();
        ms.top();

        sc.close();
    }
}
