#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
int block_size = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    // Opening file from argv.
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) // Memory safety measure.
    {
        printf("Could not open file.\n");
        return 1;
    }

    char *filename = malloc(8); // Allocating space for the name of the files.
    int file_counter = 0; // Variable that changes number os files.
    BYTE buffer[block_size]; // a buffer that each size is a byte and have a size of the block (512).
    bool foundjpeg = false; // this checks if found jpeg or not so we don't start writing gibberish before the first jpeg is found.

    sprintf(filename, "%03i.jpg", file_counter); // Giving the name of the first file.
    FILE *output = fopen(filename, "w"); // Creating the pointer that we will use to write all the files.

    if (output == NULL) // Memory safety measure.
    {
        printf("Could not create files.\n");
        return 1;
    }

    while (fread(buffer, block_size, 1, input)) // We will read until the EOF, that will return 0 and end this function.
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            // Checking if it is a reader that we are reading.
        {
            if (foundjpeg == false)
                // If it's a JPEG header and we never found a JPEG before, it's the first and we can start writing to the file.
            {
                fwrite(buffer, block_size, 1, output);
                foundjpeg = true; // So we never again return to this simple condition.
            }
            else // Now, because it is back to back, if we found the first jpeg and it's another header, we need to:
            {
                fclose(output); // Close former file.
                file_counter++; // Up the counter so we get a new filename.
                sprintf(filename, "%03i.jpg", file_counter); // Update the filename string.
                output = fopen(filename, "w"); // Open the new file (using same pointer!);
                fwrite(buffer, block_size, 1, output); // And write the header.
            }
        }
        else if (foundjpeg == true) // This way, if it's not a jpeg header and we have not found the first jpeg, nothing will be written.
        {
            fwrite(buffer, block_size, 1, output);
            // If we already found first jpeg and it's not a header, we will write to current file until it's a header (in that case, it will close and continue).
        }
    }
    //Closing every pointer and memory allocated.
    fclose(input);
    fclose(output);
    free(filename);
}