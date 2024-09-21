#include <stdio.h>
#include <string.h>
#define MAX_SIZE 30

char stack[MAX_SIZE];
int top = -1;

void push(char a)
{
    if (top == MAX_SIZE - 1)
        printf("Overflow");

    else
        stack[++top] = a;
}

char pop()
{
    if (top == -1)
    {
        return '\0';
    }
    else
        return stack[top--];
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
    char exper[30], ecopy[30];
    scanf("%[^\n]s", exper);
    int c = 0;
    int len = strlen(exper);
    for (int i = len - 1; i >= 0; i--)
    {
        if (exper[i] == ')')
            ecopy[c++] = '(';
        else if (exper[i] == '(')
            ecopy[c++] = ')';
        else
            ecopy[c++] = exper[i];
    }
    ecopy[c] = '\0';
    c = 0;
    int flag = 0;
    for (int i = 0; i < strlen(ecopy); i++)
    {
        char e = ecopy[i];
        if (e >= '0' && e <= '9')
            exper[c++] = e;
        else if (e == '(')
        {
            flag = 1;
            push(e);
        }
        else if (e == ')')
        {
            flag = 0;
            while (top != -1 && stack[top] != '(')
            {
                exper[c++] = pop();
            }
            pop();
        }
        else if (e == '+' || e == '-' || e == '*' || e == '/')
        {
            while (top != 1 && precedence(stack[top]) > precedence(e))
            {
                exper[c++] = pop();
            }
            push(e);
        }
    }
    while (top != -1)
    {
        exper[c++] = pop();
    }
    exper[c++] = '\0';
    for (int i = c - 2; i >= 0; i--)
    {
        printf("%c", exper[i]);
    }
}
