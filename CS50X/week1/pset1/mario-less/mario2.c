#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int lines = 0; lines < height; lines++)
    {
        for (int nhashes = 0; nhashes <= lines; nhashes++)
        {
            printf("#");
        }
        printf("\n");
    }
}