import java.util.Scanner;

class Swap{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        int swapnum;
        swapnum=((n&0x0F)<<4 | (n&0xF0)>>4);
        System.out.println("Original: "+n);
        System.out.println("New: "+swapnum);
    }
}