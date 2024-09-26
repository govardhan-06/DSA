#include <stdio.h>
#include <string.h>
#define MAX_SIZE 5

char queue[MAX_SIZE];
int front=-1;
int rear=-1;

void enqueue(char ch){
    if(front==-1 || rear==-1){
        front=0;
        rear=0;
        queue[rear]=ch;
    }
    else if((rear+1)%MAX_SIZE == front){
        printf("Queue is full. Cannot enqueue.\n");
    }
    else{
        rear=(rear+1)%MAX_SIZE;
        queue[rear]=ch;
        printf("Character %c is enqueued.\n",ch);
    }
}

void dequeue(){
    if(front==-1 && rear==-1){
        printf("Queue is empty.\n");
    }
    else if(front==rear){
        front=-1;
        rear=-1;
    }
    else{
        printf("Dequeued Character: %c\n",queue[front]);
        front=(front+1)%MAX_SIZE;
    }
}

void display(){
    if(front==-1 && rear==-1)
        printf("Queue is empty.\n");
    else{
        printf("Characters in the queue are: ");
        int i=front;
        while(i!=rear){
            printf("%c ",queue[i]);
            i=(i+1)%MAX_SIZE;
        }
        printf("%c\n",queue[rear]);
    }
}

int main(){
    int choice=0;
    while(choice !=4){
        scanf("%d",&choice);
        if(choice==1){
            char c=' '; 
            scanf(" %c",&c);
            enqueue(c);
        }
        else if(choice==2)
            dequeue();
        else if(choice==3)    
            display();
        else if(choice==4)
            printf("Exiting program");
        else
            printf("Invalid option.\n");
        }
}
