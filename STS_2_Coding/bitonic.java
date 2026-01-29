import java.util.*;

class Main {
    // Node structure for the Doubly Linked List [cite: 233-237]
    static class Node {
        int data; // Slide used 'date', corrected to 'data' for consistency 
        Node next;
        Node prev;
    };

    // Core function to sort the bitonic DLL [cite: 238]
    static Node sort(Node head) {
        // Base case: if list is empty or has only one node [cite: 239-240]
        if (head == null || head.next == null)
            return head;

        Node front = head; // Starts at the beginning [cite: 241]
        Node last = head; 
        
        // Move 'last' pointer to the end of the list [cite: 242, 246-247]
        while (last.next != null)
            last = last.next;

        // Dummy node to help build the result list [cite: 243-244]
        Node res = new Node();
        Node resEnd = res;
        Node next;

        // Merge process using two-pointer approach [cite: 270]
        while (front != last) {
            // If the tail value is smaller or equal [cite: 271]
            if (last.data <= front.data) {
                resEnd.next = last; // Add tail node to result [cite: 272]
                next = last.prev; // Move tail pointer backward [cite: 273]
                
                // Disconnect node and update pointers [cite: 274-276]
                if (last.prev != null) last.prev.next = null;
                last.prev = resEnd;
                last = next;
            } 
            // If the front value is smaller [cite: 279]
            else {
                resEnd.next = front; // Add front node to result [cite: 280]
                next = front.next; // Move front pointer forward [cite: 281]
                
                // Disconnect node and update pointers [cite: 282-284]
                if (front.next != null) front.next.prev = null;
                front.next = null;
                front.prev = resEnd;
                front = next;
            }
            resEnd = resEnd.next; // Progress the result list tail [cite: 285]
        }

        // Attach the final remaining node where front == last [cite: 310-311]
        resEnd.next = front;
        front.prev = resEnd;

        return res.next; // Return head of sorted list (skip dummy node) [cite: 312]
    }

    // Utility to add a node to the front of the list [cite: 314-323]
    static Node push(Node head_ref, int new_data) {
        Node new_node = new Node();
        new_node.data = new_data;
        new_node.prev = null;
        new_node.next = head_ref;
        if (head_ref != null)
            head_ref.prev = new_node;
        head_ref = new_node;
        return head_ref;
    }

    // Utility to print the list [cite: 346-353]
    static void printList(Node head) {
        if (head == null) {
            System.out.println("Doubly Linked list is empty");
            return;
        }
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of nodes:");
        int n = sc.nextInt();
        Node head = null;

        System.out.println("Enter the bitonic elements:");
        for (int i = 0; i < n; i++) {
            int m = sc.nextInt();
            // Note: push adds to front, so input 1, 2, 3 results in 3 <-> 2 <-> 1 [cite: 381-383]
            head = push(head, m);
        }

        head = sort(head); // Execute sort [cite: 385]

        System.out.println("After sorting:"); [cite: 386]
        printList(head); [cite: 387]
    }
}