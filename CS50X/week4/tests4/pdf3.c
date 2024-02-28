#include <stdio.h>
#include <cs50.h>
#include <stdint.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Improper usage.\n");
        return 1;
    }

    // Open file
    string filename = argv[1];
    FILE *file = fopen(filename, "r");
    //Check if file exists
    if (file == NULL)
    {
        printf("No such file found.\n");
        return 2;
    }

    uint8_t buffer[4];
    uint8_t signature[] = {37, 80, 68, 70};

    fread(buffer, 1, 4, file);
    fclose(file); //Already read.

    // Does the buffer signature match?
    for (int i = 0; i < 4; i++)
    {
        if (buffer[i] != signature[i])
        {
            printf("Not a PDF.\n");
            return 0;
        }
    }
    printf("It is a PDF.\n");
    return 0;
}