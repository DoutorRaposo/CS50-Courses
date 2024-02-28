#include <cs50.h>
#include <stdio.h>

const int pair_count = 3;
int locked[pair_count][pair_count];
void print2d(void);

int main (void)
{
    locked[0][0] = false;
    locked[0][1] = true;
    locked[0][2] = false;
    locked[1][0] = false;
    locked[1][1] = false;
    locked[1][2] = true;
    locked[2][0] = true;
    locked[2][1] = false;
    locked[2][2] = false;

    print2d();
}


void print2d(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            printf("%i ", (int) locked[i][j]);
        }
        printf("\n");
    }
}

