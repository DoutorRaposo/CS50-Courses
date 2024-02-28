#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
//TESTING
bool detectcycle(int winner, int loser);
void print2d(void);

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool detectcycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
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