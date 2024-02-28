// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int number_of_chars = strlen(password);

    bool lower = 0;
    bool upper = 0;
    bool number = 0;
    bool symbol = 0;

    for (int i = 0; i < number_of_chars; i++)
    {
        if (isdigit(password[i]))
        {
            number = true;
        }

        if (islower(password[i]))
        {
            lower = true;
        }

        if (isupper(password[i]))
        {
            upper = true;
        }
        if ((int) password[i] > 32 && (int) password[i] < 48)
        {
            symbol = true;
        }
    }
    if (lower == 0 || upper == 0 || number == 0 || symbol == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
