import java.util.Scanner;

class RatMaze{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();
        int arr[][]=new int[n][n];
        for(int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                arr[i][j]=sc.nextInt();
            }
        }
        solveMaze(arr,n);
    }
    public static boolean isSafe(int maze[][],int x,int y,int n){
        if(x>=0 && x<n && y>=0 && y<n && maze[x][y]==1) return true;
        else return false;
    }
    public static void printSol(int sol[][],int n){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                System.out.print(sol[i][j]+" ");
            }
            System.out.println();
        }
    }
    public static boolean solveMazeUtil(int maze[][],int sol[][],int x,int y,int n){
        if(x==n-1 && y==n-1){
            sol[x][y]=1;
            return true;
        }
        if(isSafe(maze,x,y,n)){
            sol[x][y]=1;
            
            if(solveMazeUtil(maze,sol,x+1,y,n)) return true;
            if(solveMazeUtil(maze,sol,x,y+1,n)) return true;
            sol[x][y]=0;
            
            return false;
        }
        return false;
    }
    public static void solveMaze(int maze[][],int n){
        int sol[][]=new int[n][n];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                sol[i][j]=0;
            }
        }
        if(solveMazeUtil(maze,sol,0,0,n)){
            printSol(sol,n);
        }
        else{
            System.out.println("Not solveable");
        }
    }
}