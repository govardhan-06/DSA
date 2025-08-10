import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;

class StroboNumber{
    public static boolean strobo(String num){
        Map<Character, Character> map=new HashMap<Character, Character>();
        //manually storing the mapping of digits to their 180 rotated form
        map.put('6','9');
        map.put('9','6');
        map.put('8','8');
        map.put('0','0');
        map.put('1','1');

        int l=0, r=num.length()-1;
        while(l<=r){
            // checking if the left element is there in the map
            if(!map.containsKey(num.charAt(l))) return false;
            // if the element is present then check if its mapping is equal to the element at the right
            if(map.get(num.charAt(l))!=num.charAt(r)){
                return false;
            }
            //updating the pointers
            l++;
            r--; 
        }
        return true;
    }
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter the number: ");
        String n=sc.next();
        System.out.println(strobo(n));
    }
}