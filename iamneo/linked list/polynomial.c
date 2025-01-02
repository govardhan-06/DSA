#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node
{
    int data;
    int power;
    struct Node *nextNode;
};

struct Node *createNode(int data, int power)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node *));
    newNode->data = data;
    newNode->power = power;
    newNode->nextNode = NULL;
    return newNode;
}

void insert(struct Node **head, int data, int power)
{
    struct Node *newNode = createNode(data, power);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->nextNode != NULL)
    {
        temp = temp->nextNode;
    }
    temp->nextNode = newNode;
}

void calc(struct Node **head, int val)
{
    if (*head == NULL)
    {
        printf("List is empty");
        return;
    }
    struct Node *temp = *head;
    if (temp->nextNode == NULL)
    {
        int r = (int)(temp->data * pow(val, temp->power));
        printf("%d", r);
        return;
    }
    int result = 0;
    while (temp != NULL)
    {
        result += (temp->data * pow(val, temp->power));
        // printf("%d ; %d\n",temp->data,temp->power);
        temp = temp->nextNode;
    }
    printf("%d", result);
}

int main()
{
    int power = 0;
    struct Node *head = NULL;
    scanf("%d", &power);
    for (int i = 0; i < 3; i++)
    {
        int c = 0;
        scanf("%d", &c);
        insert(&head, c, power--);
    }
    int value = 0;
    scanf("%d", &value);
    calc(&head, value);
}
