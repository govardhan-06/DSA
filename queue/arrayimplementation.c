#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

int array[MAX_SIZE];
int front = 0;
int rear = 0;

void enqueue(int e)
{
    if (rear == MAX_SIZE)
    {
        printf("Queue is full");
    }
    else
    {
        array[rear++] = e;
    }
}

int dequeue()
{
    if (front == rear)
    {
        printf("Queue is empty");
    }
    else
    {
        return array[front++];
    }
}

int peek()
{
    if (front == rear)
    {
        printf("Queue is empty");
    }
    else
    {
        return array[rear - 1];
    }
}

int main()
{
    int n = 0;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        scanf("%d", &c);
        enqueue(c);
    }
    printf("Popped out: %d\n", dequeue());

    printf("Popped out: %d\n", dequeue());

    printf("Popped out: %d\n", dequeue());
}