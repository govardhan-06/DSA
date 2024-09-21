#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 30

char stack[MAX_SIZE], prefix[MAX_SIZE];
int top = -1;

void push(char x)
{
    if (top == MAX_SIZE - 1)
    {
        printf("Overflow");
    }
    else
    {
        stack[++top] = x;
    }
}

int pop()
{
    if (top == -1)
    {
        printf("Underflow");
    }
    else
    {
        return stack[top--];
    }
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '/' || op == '*')
        return 2;
    return 0;
}

void reverse(char infix[], char rev[])
{
    int c = 0;
    for (int i = strlen(infix) - 1; i >= 0; i--)
    {
        if (infix[i] == ')')
            rev[c++] = '(';

        else if (infix[i] == '(')
            rev[c++] = ')';

        else
            rev[c++] = infix[i];
    }
    // rev[c] = '\0';
}

int main()
{
    char infix[MAX_SIZE], rev[MAX_SIZE];
    int c = 0;
    scanf("%[^\n]s", infix);
    reverse(infix, rev);
    for (int i = 0; i < strlen(rev); i++)
    {
        if (rev[i] >= '0' && rev[i] <= '9')
            prefix[c++] = rev[i];
        else if (rev[i] == '(')
            push(rev[i]);
        else if (rev[i] == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                prefix[c++] = pop();
            }
            pop();
        }
        else
        {
            while (top != -1 && precedence(stack[top]) >= precedence(rev[i]))
            {
                prefix[c++] = pop();
            }
            push(rev[i]);
        }
    }
    while (top != -1)
    {
        prefix[c++] = pop();
    }

    reverse(prefix, rev);

    rev[c] = '\0';

    printf("%s", rev);
}
