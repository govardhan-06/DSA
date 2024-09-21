#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 30

char stack[MAX_SIZE], postfix[MAX_SIZE];
int top = -1;

void push(int x)
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

int main()
{
    char exp[MAX_SIZE];
    int c = 0;
    printf("Enter the infix notation: ");
    scanf("%[^\n]s", exp);
    for (int i = 0; i < strlen(exp); i++)
    {
        if (exp[i] >= '0' && exp[i] <= '9')
            postfix[c++] = exp[i];

        else if (exp[i] == '(')
            push(exp[i]);

        else if (exp[i] == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[c++] = pop();
            }
            pop();
        }

        else
        {
            while (top != -1 && precedence(stack[top]) >= precedence(exp[i]))
                postfix[c++] = pop();
            push(exp[i]);
        }
    }

    while (top != -1)
    {
        postfix[c++] = pop();
    }

    postfix[c] = '\0';

    printf("%s", postfix);
}