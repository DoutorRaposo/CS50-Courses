#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BITS_IN_BYTE = 8;

int char_to_bit(char unit, int digit_position);

void print_bulb(int bit);

int main(void)
{
    // TODO
    string message = get_string("Message: ");
    int length = strlen(message);
    int byte[length][BITS_IN_BYTE];
    //This part is insert each character in the function that converts to binary.
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            byte[i][j] = char_to_bit(message[i], j);
        }
    }
    //This part one by one prints the information from the array. First, it prints all the numbers in a set of 8, the char (int j is inverted because it generates inverted in the function). Then, the next character starts to print.
    for (int i = 0; i < length; i++)
    {
        for (int j = BITS_IN_BYTE; j > 0 ; j--)
        {
            print_bulb(byte[i][(j - 1)]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
//This function converts to binary, but for convention of the print function, it gives a said character digit according to its position in the binary form. To achieve this, it generates the full binary then gives back only the digit in a specific position, because we can't make it give back an array.
int char_to_bit(char unit, int digit_position)
{
    int array[BITS_IN_BYTE];
    for (int i = 0; i < BITS_IN_BYTE; i++)
//we get the remainder of the number to define if the digit position is 1 or 0. Then, we divide by two so we can do it again on the next step to search for the next position.
    {
        if ((int) unit % 2 == 0)
        {
            array[i] = 0;
        }
        else
        {
            array[i] = 1;
        }
        unit = unit / 2;
    }
    return array[digit_position];
}