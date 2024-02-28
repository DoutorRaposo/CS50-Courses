#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int char_total = strlen(input);
    int digits[char_total];
    for (int i = 0; i < char_total; i++)
    {
        digits[i] = input[char_total - 1 - i] - 48;
    }
    int final = 0;
    for (int i = 0; i < char_total; i++)
    {
        final += digits[i] * pow(10, i);
    }

    return final;
}