import java.util.*;

public class Maxproduct {
    public static void main(String[] args) {
        int a[] = {-5, -4, -1, -2};
        
        int max = a[0];    // max product ending at current index
        int min = a[0];    // min product ending at current index
        int m = a[0];      // global maximum product
        int temp = 0;

        for (int i = 1; i < a.length; i++) {
            if (a[i] > 0) {
                max = Math.max(a[i], max * a[i]);
                min = Math.min(a[i], min * a[i]);
            } else if (a[i] == 0) {
                max = min = 0;
            } else { // a[i] < 0
                temp = max;
                max = Math.max(a[i], min * a[i]);
                min = Math.min(a[i], temp * a[i]);
            }
            m = Math.max(m, max); // update global max
        }

        System.out.println("Maximum product subarray: " + m);
    }
}
