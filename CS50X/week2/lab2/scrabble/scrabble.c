#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int length = strlen(word);
    int ind_scores[length];
    int sum = 0;

    for (int i = 0; i < length; i++)
    {
        if (isupper(word[i]))
        {
            ind_scores[i] = POINTS[(int) word[i] - 65];
        }
        if (islower(word[i]))
        {
            ind_scores[i] = POINTS[(int) word[i] - 97];
        }
        if (((int) word[i] < 65 || (int) word[i] > 90) && ((int) word[i] < 97 || (int) word[i] > 123))
        {
            ind_scores[i] = 0;
        }
    }

    for (int i = 0; i < length; i++)
    {
        sum += ind_scores[i];
    }

    return sum;
}
