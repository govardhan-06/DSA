import java.util.Scanner;

class Hypen{
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        String s=sc.nextLine();
        System.out.printf("Original String of length %d : %s",s.length(),s);
        String rs=rmhypen(s);
        System.out.printf("Modified String of length %d : %s",rs.length(),rs);
    }
    
    public static String rmhypen(String s){
        if(s.contains("-")){
            int i=s.indexOf("-");
            String rs="-"+s.substring(0,i)+s.substring(i+1);
            return rs;
        }
        else{
            return s;
        }
    }
};