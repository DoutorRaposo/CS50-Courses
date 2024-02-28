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
    fread(buffer, 1, 4, file);
    fclose(file);
    if (buffer[0] == 37 && buffer[1] == 80 && buffer[2] == 68 && buffer[3] == 70)
    {
        printf("This file is a PDF.\n");
        return 0;
    }
    else
    {
        printf("This file is not a PDF.\n");

        return 3;
    }
}