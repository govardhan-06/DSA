#include <stdio.h>
#include <stdlib.h>

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

void insert(int data, int power, struct Node **head)
{
    struct Node *newNode = createNode(data, power);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    struct Node *curr = *head;
    while (curr->nextNode != NULL)
    {
        curr = curr->nextNode;
    }
    curr->nextNode = newNode;
}

void compare(struct Node **head1, struct Node **head2)
{
    if (*head1 == NULL || *head2 == NULL)
    {
        printf("Out of Bounds");
        return;
    }
    struct Node *exp0 = *head1;
    struct Node *exp1 = *head2;
    while (exp0 != NULL && exp1 != NULL)
    {
        if (exp0->power != exp1->power || exp0->data != exp1->data)
        {
            printf("Polynomials are Not Equal.");
            return;
        }
        exp1 = exp0->nextNode;
        exp1 = exp1->nextNode;
    }
    printf("Polynomials are Equal.");
}

void display(struct Node **head)
{
    struct Node *temp = *head;
    while (temp != NULL)
    {
        if (temp->nextNode == NULL)
            printf("(%dx^%d)", temp->data, temp->power);
        else
            printf("(%dx^%d) + ", temp->data, temp->power);
        temp = temp->nextNode;
    }
    printf("\n");
}

int main()
{
    struct Node *head1 = NULL;
    struct Node *head2 = NULL;

    int n = 0, m = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int c1 = 0, c2 = 0;
        scanf("%d %d", &c1, &c2);
        insert(c1, c2, &head1);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int c1 = 0, c2 = 0;
        scanf("%d %d", &c1, &c2);
        insert(c1, c2, &head2);
    }
    printf("Polynomial 1: ");
    display(&head1);
    printf("Polynomial 2: ");
    display(&head2);
    compare(&head1, &head2);
}
