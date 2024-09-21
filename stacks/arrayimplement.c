#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 10

int array[MAX_SIZE];
int top = -1;

bool isEmpty()
{
    if (top == -1)
        return true;
    else
        return false;
}

bool isFull()
{
    if (top == MAX_SIZE - 1)
        return true;
    else
        return false;
}

void push(int e)
{
    if (isFull())
    {
        printf("Array is full!! Try Again");
    }
    else
    {
        array[++top] = e;
    }
}

int pop()
{
    if (isEmpty())
    {
        printf("Array is empty!!");
    }
    else
    {
        return array[top--];
    }
}

int peek()
{
    if (isEmpty())
    {
        printf("Array is empty!!");
    }
    else
    {
        return array[top];
    }
}

int main()
{
    int n = 0;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        scanf("%d", &c);
        push(c);
    }
    printf("Topmost element of stack: %d\n", peek());
    printf("Popped out: %d\n", pop());

    printf("Topmost element of stack: %d\n", peek());
    printf("Popped out: %d\n", pop());

    printf("Topmost element of stack: %d\n", peek());
    printf("Popped out: %d\n", pop());
}
