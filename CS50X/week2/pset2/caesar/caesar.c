#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool CheckArgIsNumber(char argument[]);
string cipher(string text, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || !CheckArgIsNumber(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    string ciphertext = cipher(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool CheckArgIsNumber(char argument[])
{
    //Check each char if it is a number, until it hits de /0 nul (represented by 0 in ASCII).
    for (int i = 0; argument[i] != 0; i++)
    {
        if (!isdigit(argument[i]))
        {
            return false;
        }
    }
    return true;
}

string cipher(string text, int key)
{
    int length = strlen(text);
    key = key % 26;
    for (int i = 0; i < length; i++)
        //ok, so I couldn't make this fork more elegant, but basically we get the real number of rotations of key
        //because rotating through more than once is useless (used modulo). Then, if it's upper we do the operation and circle around if it's higher than Z or z.
    {
        if (isupper(text[i]))
        {
            int j = text[i] + key;
            if (j > 90)
            {
                j -= 26;
            }
            text[i] = j;
        }
        if (islower(text[i]))
        {
            int j = text[i] + key;
            if (j > 122)
            {
                j -= 26;
            }
            text[i] = j;
        } //Ok, so it seems I have to "protect" the char from going to higher than 127. Used an int as a "buffer"
    }
    return text;
}