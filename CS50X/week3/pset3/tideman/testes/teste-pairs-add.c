#include <cs50.h>
#include <stdio.h>

void add_pairs(void);
void sort_pairs(void);




// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

const int candidate_count = 3;
int preferences[candidate_count][candidate_count];
// Array of candidates
string candidates[candidate_count];
pair pairs[candidate_count * (candidate_count - 1) / 2];

int pair_count;

int main(void)
{
    preferences[0][0] = 0;
    preferences[0][1] = 7;
    preferences[0][2] = 3;
    preferences[1][0] = 2;
    preferences[1][1] = 0;
    preferences[1][2] = 5;
    preferences[2][0] = 6;
    preferences[2][1] = 4;
    preferences[2][2] = 0;

    add_pairs();
    sort_pairs();
}

void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && preferences[i][j] > preferences [j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void)
{
    int strengths[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strengths[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
    return;
}
