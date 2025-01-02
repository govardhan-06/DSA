#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prevNode;
    struct Node *nextNode;
};

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->prevNode = NULL;
    newNode->nextNode = NULL;
    newNode->data = data;
    return newNode;
}

void insert(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
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
    newNode->prevNode = curr;
}

void rotate(struct Node **head, int k)
{
    struct Node *temp = *head;
    int length = 0;

    // finding the tail
    struct Node *tail = *head;
    while (tail->nextNode != NULL)
    {
        tail = tail->nextNode;
    }

    // length of linked list
    while (temp != NULL)
    {
        temp = temp->nextNode;
        length++;
    }

    // normalize
    k = k % length;

    if (k == 0)
        return;

    // find (length-k)th node
    temp = *head;
    for (int i = 1; i < length - k; i++)
    {
        temp = temp->nextNode;
    }

    // new head && new tail
    struct Node *new_head = temp->nextNode;
    struct Node *new_tail = temp;

    new_head->prevNode = NULL;
    new_tail->nextNode = NULL;

    (*head)->prevNode = tail;
    tail->nextNode = *head;

    *head = new_head;
}

void display(struct Node **head)
{
    struct Node *temp = *head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->nextNode;
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    struct Node *head = NULL;
    for (int i = 0; i < n; i++)
    {
        int c = 0;
        scanf("%d", &c);
        insert(&head, c);
    }
    int k = 0;
    scanf("%d", &k);
    rotate(&head, k);
    display(&head);
}
