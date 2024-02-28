#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int length;
    do
    {
        length = get_int("Length: ");
    }
    while (length < 1);

    int array[length];

    array[0] = 1;

    for (int i = 0; i < length; i++)
    {
        array[i + 1] = 2*array[i];
        printf("%i\n", array[i]);
    }
}