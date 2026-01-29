import java.util.*;

class Main {
    // Finds the index of the minimum element in the unsorted part of the queue
    public static int minIndex(Queue<Integer> list, int sortIndex) {
        int min_index = -1;
        int min_value = Integer.MAX_VALUE;
        int s = list.size();
        
        for (int i = 0; i < s; i++) {
            int current = list.peek();
            list.poll();
            
            // Only consider elements within the unsorted range
            if (current <= min_value && i <= sortIndex) {
                min_index = i;
                min_value = current;
            }
            list.add(current); // Add back to rear to maintain queue structure
        }
        return min_index;
    }

    // Moves the minimum element found at min_index to the rear of the queue
    public static void insertMinToRear(Queue<Integer> list, int min_index) {
        int min_value = 0;
        int s = list.size();
        
        for (int i = 0; i < s; i++) {
            int current = list.peek();
            list.poll();
            
            if (i != min_index) {
                list.add(current); // Re-add if it's not the minimum
            } else {
                min_value = current; // Hold the minimum element
            }
        }
        list.add(min_value); // Finally, add the minimum element to the rear
    }

    // Main sorting function
    public static void sortQueue(Queue<Integer> list) {
        for (int i = 1; i <= list.size(); i++) {
            // Find min in the remaining unsorted portion
            int min_index = minIndex(list, list.size() - i);
            // Move that min to the rear
            insertMinToRear(list, min_index);
        }
    }

    public static void main(String[] args) {
        Queue<Integer> list = new LinkedList<Integer>();
        list.add(6);
        list.add(11);
        list.add(15);
        list.add(4);

        sortQueue(list);

        // Print sorted queue
        while (list.isEmpty() == false) {
            System.out.print(list.peek() + " ");
            list.poll();
        }
    }
}