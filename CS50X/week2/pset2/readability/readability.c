#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int count_sentences(string text);
int index(int number_of_letters, int number_of_words, int number_of_sentences);

int main(void)
{
    string text = get_string("Text: ");
    int number_of_letters = count_letters(text);
    int number_of_words = count_words(text);
    int number_of_sentences = count_sentences(text);
    int grade = index(number_of_letters, number_of_words, number_of_sentences);
// Listing all possible cases in the least amount of code possible!
    if (grade < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 0 && grade < 17)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
}
// The three functions operate pretty much like the other. Could have gotten the length in main so I don't need to get every single function, but okay. For letters, I'm assuming every character is a letter.
int count_letters(string text)
{
    int length = strlen(text);
    int number_of_letters = 0;

    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            number_of_letters++;
        }
    }
    return number_of_letters;
}
// In this one I assume that every word is counted after a space and if there's a '.' it is the final punctuation if the next char is NUL.
int count_words(string text)
{
    int length = strlen(text);
    int number_of_words = 0;

    for (int i = 0; i < length; i++)
    {
        if (isblank(text[i]))
        {
            number_of_words++;
        }
        if (ispunct(text[i]) && (int) text[i + 1] == 0)
        {
            number_of_words++;
        }
    }
    return number_of_words++;
}
// In this one I'm checking if the ASCII matches and that's it. Later I should check if there's easier ways to check number of sentences in other cases.
int count_sentences(string text)
{
    int length = strlen(text);
    int number_of_sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if ((int) text[i] == 33 || (int)text[i] == 46 || (int)text[i] == 63)
        {
            number_of_sentences++;
        }
    }
    return number_of_sentences;
}
// Formula for calculating the index. Did little by little so debugging would be easier.
int index(int number_of_letters, int number_of_words, int number_of_sentences)
{
    float L = (number_of_letters / (float) number_of_words) * 100;
    float S = (number_of_sentences / (float) number_of_words) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    return (int) round(index);
}