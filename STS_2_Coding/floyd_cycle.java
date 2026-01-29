import java.util.*;

class Main{
    public static Node insertNode(Node head, int val){
        Node newNode=new Node(val);
        if(head==null){
            head=newNode;
            return head;
        }
        Node temp=head;
        while(temp.next!=null){
            temp=temp.next;
        }
        temp.next=newNode;
        return head;
    }
    
    public static boolean checkCycle(Node head){
        if(head==null){
            return false;
        }
        Node slow, fast;
        slow=head;
        fast=head;
        while(fast.next!=null && fast.next.next!=null){
            slow=slow.next;
            fast=fast.next.next;
            if(slow==fast) return true;
        }
        return false;
    }
    
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        Node head=null;
        int n=sc.nextInt();
        for(int i=0;i<n;i++){
            int m=sc.nextInt();
            head=insertNode(head,m);
        }
        head.next.next.next = head;
        if(checkCycle(head)==true){
            System.out.println("Cycle exist");
        }
        else{
            System.out.println("Cycle does not exist");
        }
    }
}

class Node{
    int num;
    Node next;
    Node(int val){
        num=val;
        next=null;
    }
}