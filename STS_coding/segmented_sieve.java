// Logic
// 1. The Segmented Sieve and Incremental Sieve are two algorithms used for finding prime numbers in a certain range.
//  
// 2. The Segmented Sieve algorithm is used to find all prime numbers within a given range `[L, R]` where `L` and `R` are two non-negative integers 
// such that `L <= R`. The basic idea behind this algorithm is to use the Sieve of Eratosthenes method to find all prime numbers up to the 
// square root of `R`, and then use these primes to eliminate all composite numbers in the range `[L, R]`.
//  
// 3. The Incremental Sieve algorithm, on the other hand, is used to find all prime numbers starting from a given number `N`. 
// The basic idea behind this algorithm is to use the Sieve of Eratosthenes method to find all prime numbers up to a certain limit, 
// say `L`, and then use these primes to check if `N + i` is a prime number for `i = 0, 1, 2, ...`.
//  
// 4. Both of these algorithms are efficient for finding prime numbers in certain ranges. The Segmented Sieve is particularly useful for 
// finding primes in large ranges, while the Incremental Sieve is useful for finding primes starting from a given number.

import java.utils.*;

class SegmentedSieve{
    public static void segsieve(int l,int h){
        boolean[] prime=new boolean[h+1];
        for(int i=2;i<h;i++){
            prime[i]=true;
        }
        for(int p=2;p*p<h;p++){
            int sm=(l/h)*p; // smallest multiple of p between l and h
            if(sm<l){
                sm+=p;
            }
            for(int i=sm;i<h;i+=p){
                prime[i]=false;
            }
        }
        for(int i=l;i<h;i++){
            if(prime[i]==true){
                System.out.print(i+" ");
            }
        }
    }
    public static void main(String[] args){
        segsieve(10,50);
    }
}