import java.util.Scanner;

class LeadersArr{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        int arr[]=new int[n];
        for(int i=0;i<n;i++){
            arr[i]=sc.nextInt();
        }
        findLeaders(arr,n);
    }
    
    public static void findLeaders(int arr[],int n){
        int max=arr[n-1];
        System.out.print(max+" ");
        for(int i=n-2;i>=0;i--){
            if(arr[i]>max){
                max=arr[i];
                System.out.print(arr[i]+" ");
            }
        }
    }
    
    
}