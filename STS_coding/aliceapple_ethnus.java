import java.util.*;

class Main {

    static int minApples(int M, int K, int N, int S, int W, int E) {
        if (M <= S * K) {
            return M;
        //in east and west, there will be min. of 1 apple
        } else if (M <= S * K + E + W) {
            return S * K + (M - S * K);
        } else {
            return -1;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter no of apples to be collected-");
        int M = sc.nextInt();

        System.out.print("Enter no of apples in each tree-");
        int K = sc.nextInt();

        System.out.print("Enter no of trees in north-");
        int N = sc.nextInt();

        System.out.print("Enter no of trees in south-");
        int S = sc.nextInt();

        System.out.print("Enter no of trees in west-");
        int W = sc.nextInt();

        System.out.print("Enter no of trees in east-");
        int E = sc.nextInt();

        int ans = minApples(M, K, N, S, W, E);
        System.out.println(ans);
    }
}