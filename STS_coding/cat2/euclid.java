import java.util.Scanner;

class Euclid{
    public static int gcd(int a,int b){
        if(a==0){
            return b;
        }
        return gcd(b%a,a);
    }
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int a=sc.nextInt();
        int b=sc.nextInt();
        System.out.println("The GCD of the two numbers: "+a+" and "+b+"is: "+gcd(a,b));
    }
}