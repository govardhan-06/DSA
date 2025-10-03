import java.util.Scanner;

class ToggleSwitch{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the number of monkeys: ");
        int monkeys=sc.nextInt();
        int openCount=0, closedCount=0;
        boolean d[]=new boolean[monkeys+1];

        for(int i=1;i<=monkeys;i++){ // for ith monkey
            for(int j=i;j<=monkeys;j+=i){ // toggle door logic
                d[j]=!d[j];
            }
        }

        for(int i=1;i<=monkeys;i++){
            if(d[i]) openCount++;
            else closedCount++;
        }
        
        System.out.println("Number of doors opened: "+openCount);
        System.out.println("Number of doors closed: "+closedCount);
    }
}