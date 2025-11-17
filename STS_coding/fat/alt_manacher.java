import java.util.Scanner;

class Palindrome{
    public static boolean isPalindrome(String s,int left,int right){
        while(left<=right){
            if(s.charAt(left)!=s.charAt(right)){
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        String s=sc.nextLine();
        int n=s.length();
        
        int maxlen=Integer.MIN_VALUE;
        int start=0;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(isPalindrome(s,i,j) && j-i+1 > maxlen){
                    maxlen=j-i+1;
                    start=i;
                }
            }
        }
        System.out.println(s.substring(start,start+maxlen));
    }
}