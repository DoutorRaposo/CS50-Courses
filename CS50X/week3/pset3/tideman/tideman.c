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
//MY FUNCTIONNN
bool detectcycle(int winner, int loser);

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            //This part is the important one: rank defines which one it's querying and ranks[] is the storing part. i is the exact candidate index.
            return true;
        }
    }
    return false;
}

// Always -> Rank [0][1] > Rank [0][2] then Rank [1][2]. That's why j = i + 1 to the limitation of candidate_count.
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

//Check all the preferences 2d array and if one vote is higher than the other, the winner and loser of that pair is registered and the pair_count ups.
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
            if (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner] <
                preferences[pairs[j + 1].winner][pairs[j + 1].loser] - preferences[pairs[j + 1].loser][pairs[j + 1].winner])
                //LOL. Maybe try creating temporary ints just to better readability? Check TEMPS for reference later.
            {
                temporary[j].winner = pairs[j].winner;
                temporary[j].loser = pairs[j].loser;
                pairs[j].winner = pairs[j + 1].winner;
                pairs[j].loser = pairs[j + 1].loser;
                pairs[j + 1].winner = temporary[j].winner;
                pairs[j + 1].loser = temporary[j].loser;
            }
        }
    }
    return;
}

void lock_pairs(void)
{
    // I figured how to fill the locked array by associating that it is locked[winner][loser] that states if there's an edge. Now we need to check if there's a cycle. For that, I'm trying to abstract  the checking creating a function that detects a cycle/if's there's a cycle.
    for (int i = 0; i < pair_count; i++)
    {
        if (!detectcycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}


// To detect the cycle, we have to check if the current loser of the locking won anyone winning the original candidate that was winner. Or if anyone that the loser won also didn't already won the loser.
// What helped me think is to assume that we have an already stabilished link of A > B > C > D (keep it simple saying that the sorted was (A > B) (B > C) (C > D)) and a sorted pair of D > B enters the function last.
// The winner ("D") is called repeatedly as "winner", basically checking the chain before him. The "catch" is that only in the cases that the "loser" won someone (a way to stabilish that it's a chain?).
// Is locked[B][D] true? Better, does B win D? No. So in the cases that B win (in this case, against C), it will check if there's a cycle between D and C.
// Is locked[C][D] true, namely, does C win D? Yes, so return true. Which means it confirmed a cycle between D and C, which means it confirmed a cycle between D and B,
// Which means that in the other function (lock_pairs) it will not register as "true" locked_pair, remaining "false".
// Muita tentativa e erro. Ler depois para entender melhor a recursão, graphs e busca de graph.
bool detectcycle(int winner, int loser)
{
    if (locked[loser][winner]) // If a previous higher importance pair already estabilished a link of winning this pair winner, it is a cycle. The most basic type. Base case?
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i]) //Trying to create a "chain". Basically, in all the cases that the loser won >
        {
            //> we proceed to check if there's one that in which the one original winner already won those which lost to the loser.
            if (detectcycle(winner, i))
                //Remember this for graphs > the same value (winner) remaining over the recursion appears to be essential.
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
    // Ok, so using the example before for A > B > C > D, I drawed a "truth table" and apparently if there's no edge going TO the candidate, he MUST be the source.
    //    A  B  C  D
    // A  0  1  0  0
    // B  0  0  1  0
    // C  0  0  0  1
    // D  0  0  0  0
    // A vertical line that is ALL FALSE means source (and a horizontal that is ALL FALSE means least preferred!)
    // Vertical is the first [] in locked[][] and horizontal the second. At least it's what I used in sheets.
    // We need to check if the second [] have all falses! (FIX THE VERTICAL). So iterate over all first []'s. (VARIATE THE HORIZONTAL).
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i]) //if no one connects to [i], it's the source!
            {
                false_count++;
            }
        }
        if (false_count == candidate_count) //Confirms that no one connects.
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}