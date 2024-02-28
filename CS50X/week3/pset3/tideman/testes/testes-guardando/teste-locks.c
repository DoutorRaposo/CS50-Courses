#include <cs50.h>
#include <stdio.h>

void lock_pairs(void);
void print2d(void);
bool detectcycle(int winner, int loser);

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

const int candidate_count = 4;
int preferences[candidate_count][candidate_count];
// Array of candidates
string candidates[candidate_count];
pair pairs[candidate_count * (candidate_count - 1) / 2];

int pair_count = candidate_count;
bool locked[candidate_count][candidate_count];

int main(void)
{
    pairs[0].winner = 3;
    pairs[0].loser = 0;
    pairs[1].winner = 0;
    pairs[1].loser = 1;
    pairs[2].winner = 1;
    pairs[2].loser = 2;
    pairs[3].winner = 2;
    pairs[3].loser = 0;
    pairs[4].winner = 3;
    pairs[4].loser = 1;
    pairs[5].winner = 3;
    pairs[5].loser = 2;


    lock_pairs();
    print2d();
}

void lock_pairs(void)
{
    // I figured how to fill the locked array by associating that it is locked[winner][loser] that states if there's an edge. Now we need to check if there's a cycle.
    for (int i = 0; i < pair_count; i++)
    {
        if (!detectcycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool detectcycle(int winner, int loser)
{
    if (locked[loser][winner]) // If a previous higher importance pair already estabilished a link of winning this pair winner, it is a cycle.
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i]) //Basically, in all the cases that the loser won.
        {
            if (detectcycle(winner, i)) //Check if there's one that in which the one original winner already won those which lost to the loser.
            {
                return true;
            }
        }
    }
    return false;
}

void print2d(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", (int) locked[i][j]);
        }
        printf("\n");
    }
}