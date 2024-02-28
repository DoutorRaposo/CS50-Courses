#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    for (int i = 0; i < argc - 1; i++)
    {
        printf("%c\n", argv[i + 1][0]);
    }
}