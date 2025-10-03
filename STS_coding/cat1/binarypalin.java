import java.util.Scanner;

class BinaryPalindrome{
    public static boolean isPalin(int n){
        int reversed=0;
        int orginal=n;
        while(orginal>0){
            reversed<<=1;  // Left shift by 1 bit (to make space for the new digit from orginal)
            reversed |= (orginal&1);  // Append the least significant bit of 'x' to'reversed'
            orginal>>=1;  // Right shift by 1 bit to remove the digit which has already been appended to the reversed
        }
        return reversed==n;
    }
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the number: ");
        int x=sc.nextInt();
        if(isPalin(x)){
            System.out.println("Binary Palindrome");
        }
        else{
            System.out.println("Not a binary palindrome");
        }
    }
}