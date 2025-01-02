#include <stdio.h>
#define MAX_SIZE 10

int deque[MAX_SIZE];
int front = -1;
int rear = -1;

void enqueuefront(int n)
{
    if (front == 0 && rear == MAX_SIZE - 1 || front == rear + 1)
    {
        printf("Queue is full\n");
    }
    else if (front == -1 && rear == -1)
    {
        front = rear = 0;
        deque[front] = n;
    }
    else if (front == 0)
    {
        front = MAX_SIZE - 1;
        deque[front] = n;
    }
    else
    {
        front--;
        deque[front] = n;
    }
}

void enqueuerear(int n)
{
    if (front == 0 && rear == MAX_SIZE - 1 || front == rear + 1)
    {
        printf("Queue is full\n");
    }
    else if (front == -1 && rear == -1)
    {
        front = rear = 0;
        deque[rear] = n;
    }
    else if (rear == MAX_SIZE - 1)
    {
        rear = 0;
        deque[rear] = n;
    }
    else
    {
        rear++;
        deque[rear] = n;
    }
}

void getdisplay()
{
    if (front == -1 && rear == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");
    int i = front;
    while (1)
    {
        printf("%d ", deque[i]);
        if (i == rear)
            break;              // Exit condition
        i = (i + 1) % MAX_SIZE; // Circular increment
    }
    printf("\n");
}

void dequeuefront()
{
    if (front == -1 && rear == -1)
    {
        printf("Queue is empty\n");
    }
    else if (front == rear)
    {
        printf("Popped out from front: %d\n", deque[front]);
        front = rear = -1; // Queue becomes empty
    }
    else
    {
        printf("Popped out from front: %d\n", deque[front]);
        front = (front + 1) % MAX_SIZE; // Circular increment
    }
}

void dequeuerear()
{
    if (front == -1 && rear == -1)
    {
        printf("Queue is empty\n");
    }
    else if (front == rear)
    {
        printf("Popped out from rear: %d\n", deque[rear]);
        front = rear = -1; // Queue becomes empty
    }
    else
    {
        printf("Popped out from rear: %d\n", deque[rear]);
        rear = (rear - 1 + MAX_SIZE) % MAX_SIZE; // Circular decrement
    }
}

int main()
{
    int ch = 0;
    int c = 0;

    printf("Deque Operations Menu:\n");
    printf("1. Enqueue Front\n");
    printf("2. Enqueue Rear\n");
    printf("3. Dequeue Front\n");
    printf("4. Dequeue Rear\n");
    printf("0. Display Queue\n");
    printf("4. Exit\n");

    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &ch);
        if (ch == 1)
        {
            printf("Enter number to enqueue at front: ");
            scanf("%d", &c);
            enqueuefront(c);
        }
        else if (ch == 2)
        {
            printf("Enter number to enqueue at rear: ");
            scanf("%d", &c);
            enqueuerear(c);
        }
        else if (ch == 3)
        {
            dequeuefront();
        }
        else if (ch == 4)
        {
            dequeuerear();
        }
        else if (ch == 0)
        {
            getdisplay();
        }
        else
        {
            printf("Exiting the program.\n");
            break;
        }
    }
    return 0;
}