#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1

    if (argc != 3) // 1 is the name of the program, 2 is the input and 3 is the output.
    {
        printf("Try: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2

    // Opening the file and checking for NULL!
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Read header
    // TODO #3

    // created a struct to receive all the information from the header by asking the read function to read 1 unit the size of the full header.
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    // If the function returns false, stop the program.
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 2;
    }

    // Open output file for writing
    // TODO #5

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not create output file.\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    // Basically write everything in header to file.
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    // Now using the function to get the value.

    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8

    // First, defining a pointer that has the block size. the optional exercise said that it was a uint16_t, but didn't work out for me, at least.
    // Felt safer using exactly the size of the block in the memory.
    // Apparently the exercise asks for array, but it worked like this. I guess it is interchangeable.
    BYTE *buffer = malloc(block_size);

    // Second, seeking the end and adding one block further, because the first thing fseek will do next is go back two blocks.
    // Meaning, it will read the bytes one block removed from the end through the ending byte, then write it.
    fseek(input, - block_size, SEEK_END);

    // printf("Current place is: %li.Total size minus header should be: %u.\n", ftell(input), header.subchunk2Size + 44);

    // Then, finally, making the while loop last until the position of the pointer is one block away before the header.
    // That is because read will always finish one step ahead, advancing the ftell by one block.
    // If we don't put this in the expression, a bit of code of the header will be displayed as sound.
    // That means it will finish the iteration with the last chunk, say, 44, and will go back 2*4, to 40, and write 40 to 44, which is not the data we need.
    // One of the hardest details. Always ends up ending with a bzzzt sound if you miss it.
    // Does that mean the number of chunks is always even? One for each channel maybe?
    while (ftell(input) >= sizeof(WAVHEADER))
    {
        fread(buffer, block_size, 1, input); //therefore reading the current position.
        fwrite(buffer, block_size, 1, output); // and adding in reverse order.
        fseek(input, - 2 * block_size, SEEK_CUR); //to compensate for fread advancing, we get two behind.
    }

    //Lastly, free the memories from heap.
    free(buffer);
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    // Created a string that cointains the text in header.format and compared it to the inserted header.
    char *format = "WAVEfmt";
    if (strcmp((char *)header.format, format))
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}