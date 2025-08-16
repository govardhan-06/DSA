import java.util.*;

class EulerPhi{
    public static int euler(int n){
        int result=n;
        //get the prime factors
        for(int i=2;i*i<=n;i++){
            if(n%i==0){
                while(n%i==0){
                    n/=i;
                }
                result-=result/i;
            }
        }
        if(n>1){
            result-=result/n;
        }
        return result;
    }
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        System.out.println(euler(n));
    }
}
