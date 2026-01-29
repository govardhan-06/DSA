import java.util.*;

class Main {

    static class Node {
        int data;
        int priority;
        Node next, prev;

        Node(int data, int priority) {
            this.data = data;
            this.priority = priority;
        }
    }

    static Node head = null;

    // Insert element based on priority
    static void push(int data, int priority) {
        Node node = new Node(data, priority);

        // If queue is empty
        if (head == null) {
            head = node;
            return;
        }

        Node temp = head;
        Node parent = null;

        // Traverse till lower priority found
        while (temp != null && temp.priority >= priority) {
            parent = temp;
            temp = temp.next;
        }

        // Insert at beginning
        if (parent == null) {
            node.next = head;
            head.prev = node;
            head = node;
        }
        // Insert at end
        else if (temp == null) {
            parent.next = node;
            node.prev = parent;
        }
        // Insert in middle
        else {
            parent.next = node;
            node.prev = parent;
            node.next = temp;
            temp.prev = node;
        }
    }

    // Return highest priority element
    static int peek() {
        if (head != null)
            return head.data;
        return -1;
    }

    // Remove highest priority element
    static int pop() {
        if (head == null)
            return -1;

        int value = head.data;
        head = head.next;

        if (head != null)
            head.prev = null;

        return value;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        for (int i = 0; i < n; i++) {
            int data = sc.nextInt();
            int priority = sc.nextInt();
            push(data, priority);
        }

        System.out.println(peek());
        System.out.println(pop());
        System.out.println(pop());
        System.out.println(peek());

        sc.close();
    }
}
