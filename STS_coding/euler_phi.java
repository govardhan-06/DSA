import java.util.Scanner;

class EulerPhiAlgo{
    public static int eulerphi(int n){
        int result=n;

        for(int p=2;p*p<n;p++){
            // To get the prime factors of n
            if(n%p==0){
                // To remove the multiples of p
                while(n%p==0){
                    n/=p;
                }
                result-=result/p;
            }
        }
        // To remove the influence of prime factors greater than sqrt(n)
        if(n>1){
            result-=result/n;
        }
        return result;
    }
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the number: ");
        int n=sc.nextInt();
        System.out.println("The entered number: "+n);
        int phiNum=eulerphi(n);
        System.out.println("Result: "+phiNum);
    }
}