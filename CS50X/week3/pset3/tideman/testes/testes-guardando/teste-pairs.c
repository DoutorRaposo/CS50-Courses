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
bool locked[candidate_count][candidate_count];

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
//Applied similar concept to the TEMPS exercise. Tried to separate the strengths before, but felt I could do with fewer lines of code.
//In essence, we check if the diference inside a struct is higher than the other then we swap!
//Hard to visualize, but basically we can get the preference[][] by using the pairs in the array part of the preference. Then we invert to check diference. Then check which of the diferences is higher.
void sort_pairs(void)
{
    pair temporary[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] < preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner])
            {
                temporary[j].winner = pairs[j].winner;
                temporary[j].loser = pairs[j].loser;
                pairs[j].winner = pairs[j + 1].winner;
                pairs[j].loser = pairs[j + 1].loser;
                pairs[j + 1].winner= temporary[j].winner;
                pairs[j + 1].loser = temporary[j].loser;
            }
        }
    }
    return;
}