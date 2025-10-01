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
        int leaders[]=new int[n];
        int c=-1;
        int isLeader=1;
        for(int i=0;i<n-1;i++){
            isLeader=1;
            for(int j=i+1;j<n;j++){
                if(arr[i]<=arr[j]){
                    isLeader=0;
                    break;
                }
            }
            if(isLeader==1) leaders[++c]=arr[i];
        }
        for(int i=0;i<=c;i++){
            System.out.println(leaders[i]+" ");
        }
    }
}