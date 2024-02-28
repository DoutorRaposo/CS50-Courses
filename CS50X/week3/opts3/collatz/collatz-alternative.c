#include <stdio.h>
#include <cs50.h>

int collatz(int n);
int main(void)
{
    int n;
    do
    {
        n = get_int("Number: ");
    }
    while (n < 1);

    int steps = collatz(n);
    printf("Steps: %i\n", steps);
}

int collatz(int n)
{

    if (n == 1)
        return 0;
    else if (n % 2 == 0)
        return 1 + collatz(n/2);
    else
        return 1 + collatz(3*n + 1);
}