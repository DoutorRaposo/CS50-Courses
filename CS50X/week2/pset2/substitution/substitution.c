//i'm going to reuse some of the code that I did for caesar problem.
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

string cipher(string text, string key);
bool isKeyValid(string key);
const int key_length = 26;

int main(int argc, string argv[])
{
    //Checking if the number of arguments is correct.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Checking if the key is valid.
    if (!isKeyValid(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //Getting plaintext.
    string plaintext = get_string("plaintext: ");
    //Getting the text to run in the ciphertext function.
    string ciphertext = cipher(plaintext, argv[1]);

    //Printing the cipher and returning 0.
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool isKeyValid(string key)
{
    //First, the key must have 26 characters.
    if (strlen(key) != key_length)
    {
        return false;
    }
    //Second, check if all characters are letters.
    for (int i = 0; i < key_length; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
    }
    //Third, the key must have only one of each character. For this, I checked every key if it matches the other. Just excluding the key from comparing itself and converted them all to Upper so the same character in diferent cases were compared as the same.
    for (int i = 0; i < key_length; i++)
    {
        for (int j = 0; j < key_length; j++)
        {
            if (i != j)
            {
                if (toupper(key[i]) == toupper(key[j]))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

//This was quite easy after Caesar. Basically change the character to the character in the key, defined by its position
//in the alphabet converting from the number identified in ASCII (65 for upper and 97 for lower). The toupper and tolower just guarantee the key doesn't affect the original case of the text
string cipher(string text, string key)
{
    int lengthtext = strlen(text);
    for (int i = 0; i < lengthtext; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = toupper(key[(int) text[i] - 65]);
        }
        if (islower(text[i]))
        {
            text[i] = tolower(key[(int) text[i] - 97]);
        }
    }
    return text;
}