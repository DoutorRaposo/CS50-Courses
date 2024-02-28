#include <cs50.h>
#include <stdio.h>

void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool detectcycle(int winner, int loser);

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

    candidates[0] = "Rafael";
    candidates[1] = "Dayane";
    candidates[2] = "Celeste";

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
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

//To detect the cycle, we have to check if the current loser of the locking won anyone winning the original candidate that was winner. Or if anyone that the loser won also didn't already won of the loser.
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

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int col = 0; col < candidate_count; col++)
    {
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col] == true)
            {
                break;
            }
            else if (row == candidate_count - 1)
            {
                printf("%s\n", candidates[col]);
            }
        }
    }
    return;
}