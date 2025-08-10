import java.util.Scanner;

//Chineese Remainder Theorem

class CRT{
    public static int findCRT(int size, int div[],int rem[]){
        int x=1,j;
        while(true){
            for(j=0;j<size;j++){
                if(x%div[j]!=rem[j]) break;
            }
            if(j==size) return x;
            x++;
        }
    }
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the size: ");
        int size=sc.nextInt();
        int div[]=new int[size];
        int rem[]=new int[size];
        System.out.print("Enter the divisors one by one: ");
        for(int i=0;i<size;i++){
            div[i]=sc.nextInt();
        }
        System.out.print("\n");
        System.out.print("Enter the remainders one by one: ");
        for(int i=0;i<size;i++){
            rem[i]=sc.nextInt();
        }
        System.out.print("\n");
        System.out.println(findCRT(size,div,rem));
    }
}