import java.util.*;

class Main {
    Node head;

    class Node {
        int data;
        Node next;
        Node(int d) {
            data = d;
            next = null;
        }
    }

    public void segregateEvenOdd() {
        Node evenStart = null;
        Node evenEnd = null;
        Node oddStart = null;
        Node oddEnd = null;
        Node currentNode = head;

        while (currentNode != null) {
            int element = currentNode.data;

            if (element % 2 == 0) {
                // Handle Even Nodes
                if (evenStart == null) {
                    evenStart = currentNode;
                    evenEnd = evenStart;
                } else {
                    evenEnd.next = currentNode;
                    evenEnd = evenEnd.next;
                }
            } else {
                // Handle Odd Nodes
                if (oddStart == null) {
                    oddStart = currentNode;
                    oddEnd = oddStart;
                } else {
                    oddEnd.next = currentNode;
                    oddEnd = oddEnd.next;
                }
            }
            currentNode = currentNode.next;
        }

        // If either list is empty, no segregation is needed
        if (oddStart == null || evenStart == null) {
            return;
        }

        // Connect the end of the even list to the start of the odd list
        evenEnd.next = oddStart;
        oddEnd.next = null;
        head = evenStart;
    }

    // Utility to add a new node at the beginning
    void push(int new_data) {
        Node new_node = new Node(new_data);
        new_node.next = head;
        head = new_node;
    }

    // Utility to print the linked list
    void printList() {
        Node temp = head;
        while (temp != null) {
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    public static void main(String args[]) {
        Main main = new Main();
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Enter number of nodes:");
        int n = sc.nextInt();
        
        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            int m = sc.nextInt();
            main.push(m);
        }

        System.out.println("Original List:");
        main.printList();

        main.segregateEvenOdd();

        System.out.println("Segregated List (Even then Odd):");
        main.printList();
    }
}