#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* nextNode;
    struct Node* prevNode;
};

struct Node* createNode(int data){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->nextNode=NULL;
    newNode->prevNode=NULL;
    newNode->data=data;
    return newNode;
}

void insert(struct Node** head,int data){
    struct Node* newNode=createNode(data);
    if(*head==NULL){
        *head=newNode;
        return;
    }
    newNode->nextNode=*head;
    (*head)->prevNode=newNode;
    *head=newNode;
}

int calc(struct Node* head,int sum){
    struct Node* temp=head->nextNode;
    while(temp!=NULL){
        if(head->data + temp->data == sum){
            printf("(%d, %d)\n",head->data,temp->data);
            return 1;
        }
        temp=temp->nextNode;
    }
    return 0;
}

int main(){
    int n=0;
    scanf("%d",&n);
    struct Node* head=NULL;
    for(int i=0;i<n;i++){
        int c=0;
        scanf("%d",&c);
        insert(&head,c);
    }
    int sum=0;
    scanf("%d",&sum);
    struct Node* temp=head;
    int flag=0;
    while(temp->nextNode!=NULL){
        int r=calc(temp,sum);
        if(r==1)
            flag=1;
        temp=temp->nextNode;
    }
    if(flag==0){
        printf("No pair found");
    }
}
