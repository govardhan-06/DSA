import java.util.Scanner;

class Node {
    int data;
    Node next, prev;

    Node(int val) {
        data = val;
        next = null;
        prev = null;
    }
}

class Solution {

    // Split DLL into two halves
    Node split(Node head) {
        Node slow = head, fast = head;

        while (fast.next != null && fast.next.next != null) {
            fast = fast.next.next;
            slow = slow.next;
        }

        Node second = slow.next;
        slow.next = null;

        if (second != null)
            second.prev = null;

        return second;
    }

    // Merge sort on DLL
    Node mergeSort(Node head) {
        if (head == null || head.next == null)
            return head;

        Node second = split(head);

        head = mergeSort(head);
        second = mergeSort(second);

        return merge(head, second);
    }

    // Merge two sorted DLLs
    Node merge(Node first, Node second) {
        if (first == null)
            return second;
        if (second == null)
            return first;

        if (first.data < second.data) {
            first.next = merge(first.next, second);
            if (first.next != null)
                first.next.prev = first;
            first.prev = null;
            return first;
        } else {
            second.next = merge(first, second.next);
            if (second.next != null)
                second.next.prev = second;
            second.prev = null;
            return second;
        }
    }
}

public class Main {

    static void printListLeftToRight(Node head) {
        while (head != null) {
            System.out.print(head.data + " ");
            head = head.next;
        }
        System.out.println();
    }

    static void printListRightToLeft(Node head) {
        if (head == null) return;

        Node tail = head;
        while (tail.next != null)
            tail = tail.next;

        while (tail != null) {
            System.out.print(tail.data + " ");
            tail = tail.prev;
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        Node head = null, tail = null;

        for (int i = 0; i < n; i++) {
            int val = sc.nextInt();
            Node nd = new Node(val);

            if (head == null) {
                head = tail = nd;
            } else {
                nd.next = head;
                head.prev = nd;
                head = nd;
            }
        }

        Solution sol = new Solution();
        Node res = sol.mergeSort(head);

        printListLeftToRight(res);
        printListRightToLeft(res);

        sc.close();
    }
}
