import java.util.Scanner;

class AliceApt{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int sum=0,cnt=0;
        System.out.print("Enter the number of apples: ");
        int apple=sc.nextInt();
        System.out.println();
        // we need to find the value of cnt such that sum of apples from layer 1 to cnt≥apple
        // sum : total apples from 1 to cnt layer
        // apple: total apples given as the input
        // cnt: layer count
        while(sum<apple){
            cnt++;
            sum+=(12*cnt*cnt);
        }
        // cnt: sum of apples from layer 1 to cnt ≥ apple
        System.out.println(8*cnt);
    }
}