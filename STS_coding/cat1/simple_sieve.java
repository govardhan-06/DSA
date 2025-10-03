// To find prime numbers, the Simple Sieve Algorithm is used

// Logic:
// 1. Create a list of consecutive integers from 2 through the limit.
// 2. Set a variable p to 2, the smallest prime number.
// 3. Cross out all multiples of p from the list, starting from p^2.
// 4. Find the next number in the list that is not crossed out. This is the next prime number.
// 5. Set p to the next prime number found in step 4 and repeat steps 3-5 until p^2 is greater than the limit.
// 6. The remaining numbers in the list are all prime numbers.

import java.util.*;

class SimpleSieve{
    public static void sieve(int n){
        boolean prime[]=new boolean[n+1];
        for(int i=2;i<n+1;i++){
            prime[i]=true;
        }
        for(int i=2;i*i<=n;i++){
            if(prime[i]){
                for(int j=i*i;j<=n;j+=i){
                    prime[j]=false;
                }
            }
        }
        for(int i=2;i<n+1;i++){
            if(prime[i]){
                System.out.print(i+" ");
            }
        }
        System.out.println();
    }
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the number: ");
        int n=sc.nextInt();
        sieve(n);
    }
}