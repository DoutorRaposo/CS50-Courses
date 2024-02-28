#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int steps = 0;

int main(void)
{
    int n;
    do
    {
        n = get_int("Number: ");
    }
    while (n < 1);

    steps = collatz(n);
    printf("Steps: %i\n", steps);
}

int collatz(int n)
{

    if (n == 1)
    {
        return steps;
    }
    else
    {
        steps++;
        if (n % 2 == 0)
            collatz(n/2);
        if (n % 2 != 0)
            collatz(3*n + 1);
        return steps;
    }
}