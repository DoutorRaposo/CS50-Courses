#include <cs50.h>
#include <stdio.h>
#include <string.h>


const int candidate_count = 3;
int preferences[candidate_count][candidate_count];
string candidates[candidate_count] = {"Rafael", "Dayane", "Celeste"};
int pair_count;

void record_preferences(int ranks[]);
bool vote(int rank, string name, int ranks[]);

void print2d(void);

int main(void)
{
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

        //print2d();

}

// This is basically checking if the name exists and recording.
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if(!strcmp(name, candidates[i]))
        {
            ranks[rank] = i; //This part is the important one: rank defines which one it's querying and ranks[] is the storing part. i is the exact candidate index.
            return true;
        }
    }
    return false;
}

// Always -> Rank [0][1] > Rank [0][2] then Rank [1][2]. That's why j = i + 1 to the limitation of candidate_count.
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

void print2d(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
}