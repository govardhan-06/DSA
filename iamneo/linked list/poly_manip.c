#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int coeff;
    int power;
    struct Node *nextNode;
};

struct Node *createNode(int coeff, int power)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->nextNode = NULL;
    return newNode;
}

void insertNode(struct Node **headref, int coeff, int power)
{
    struct Node *newNode = createNode(coeff, power);
    if (*headref == NULL)
    {
        *headref = newNode;
        return;
    }
    struct Node *temp = *headref;
    while (temp->nextNode != NULL)
    {
        temp = temp->nextNode;
    }
    temp->nextNode = newNode;
}

void calculate(struct Node **head1, struct Node **head2, struct Node **head3)
{
    struct Node *exp1 = *head1;
    struct Node *exp2 = *head2;
    while (exp1 != NULL & exp2 != NULL)
    {
        if (exp1->power == exp2->power)
        {
            insertNode(head3, exp1->coeff + exp2->coeff, exp2->power);
            exp1 = exp1->nextNode;
            exp2 = exp2->nextNode;
        }
        else if (exp1->power > exp2->power)
        {
            insertNode(head3, exp1->coeff, exp1->power);
            exp1 = exp1->nextNode;
        }
        else if (exp1->power < exp2->power)
        {
            insertNode(head3, exp2->coeff, exp2->power);
            exp2 = exp2->nextNode;
        }
    }
    while (exp1 != NULL)
    {
        insertNode(head3, exp1->power, exp1->power);
        exp1 = exp1->nextNode;
    }
    while (exp2 != NULL)
    {
        insertNode(head3, exp2->power, exp2->power);
        exp2 = exp2->nextNode;
    }
}

void printNode(struct Node *headref)
{
    struct Node *temp = headref;
    while (temp != NULL)
    {
        if (temp->nextNode == NULL)
            printf("(%dx^%d)", temp->coeff, temp->power);
        else
            printf("(%dx^%d) + ", temp->coeff, temp->power);
        temp = temp->nextNode;
    }
    printf("\n");
}

int main()
{
    struct Node *head1 = NULL;
    struct Node *head2 = NULL;
    struct Node *head3 = NULL;

    // Polynomial 1: 3x^3 + 2x^2 + 1
    insertNode(&head1, 3, 3);
    insertNode(&head1, 2, 2);
    insertNode(&head1, 1, 0);

    // Polynomial 2: 5x^2 + 4x + 2
    insertNode(&head2, 5, 2);
    insertNode(&head2, 4, 1);
    insertNode(&head2, 2, 0);

    printf("Polynomial 1: ");
    printNode(head1);

    printf("Polynomial 2: ");
    printNode(head2);

    calculate(&head1, &head2, &head3);

    printf("Resultant Polynomial: ");
    printNode(head3);

    return 0;
}
