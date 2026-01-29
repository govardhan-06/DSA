import java.util.*;

class Main {

    class Stack {
        int capacity;
        int top;
        int[] array;
    }

    Stack createStack(int capacity) {
        Stack stack = new Stack();
        stack.capacity = capacity;
        stack.top = -1;
        stack.array = new int[capacity];
        return stack;
    }

    static boolean isFull(Stack stack) {
        return stack.top == stack.capacity - 1;
    }

    static boolean isEmpty(Stack stack) {
        return stack.top == -1;
    }

    static void push(Stack stack, int item) {
        if (isFull(stack))
            return;
        stack.array[++stack.top] = item;
    }

    static int pop(Stack stack) {
        if (isEmpty(stack))
            return Integer.MIN_VALUE;
        return stack.array[stack.top--];
    }

    static void moveDisk(Stack src, Stack dest, char s, char d) {
        int p1 = pop(src);
        int p2 = pop(dest);

        // Source empty
        if (p1 == Integer.MIN_VALUE) {
            push(src, p2);
            System.out.println("Move disk " + p2 + " from " + d + " to " + s);
        }
        // Destination empty
        else if (p2 == Integer.MIN_VALUE) {
            push(dest, p1);
            System.out.println("Move disk " + p1 + " from " + s + " to " + d);
        }
        // Source disk bigger
        else if (p1 > p2) {
            push(src, p1);
            push(src, p2);
            System.out.println("Move disk " + p2 + " from " + d + " to " + s);
        }
        // Destination disk bigger
        else {
            push(dest, p2);
            push(dest, p1);
            System.out.println("Move disk " + p1 + " from " + s + " to " + d);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int num_of_disks = sc.nextInt();

        Main ob = new Main();

        Stack source = ob.createStack(num_of_disks);
        Stack destination = ob.createStack(num_of_disks);
        Stack auxiliary = ob.createStack(num_of_disks);

        char s = 'S', d = 'D', a = 'A';

        // If number of disks is even, swap destination and auxiliary
        if (num_of_disks % 2 == 0) {
            char temp = d;
            d = a;
            a = temp;
        }

        int total_moves = (int) (Math.pow(2, num_of_disks) - 1);

        // Push disks to source
        for (int i = num_of_disks; i >= 1; i--) {
            push(source, i);
        }

        // Perform moves
        for (int i = 1; i <= total_moves; i++) {
            if (i % 3 == 1)
                moveDisk(source, destination, s, d);
            else if (i % 3 == 2)
                moveDisk(source, auxiliary, s, a);
            else
                moveDisk(auxiliary, destination, a, d);
        }

        sc.close();
    }
}
