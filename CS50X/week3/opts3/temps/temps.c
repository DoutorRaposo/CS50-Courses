// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    // Add your code here
    avg_temp temporary[NUM_CITIES];

    for (int i = 0; i < NUM_CITIES; i++)
    {
        for (int j = 0; j < NUM_CITIES - i - 1; j++) //Max number of J must be 8 because in a case that it is 9, it will reach 10 and overflow the array. So, NUM_CITIES (10) - min_value_of_i (0) - 1. Each time i increases, we ignore the last line, that already "bubbled".
        {
            if (temps[j].temp < temps[j + 1].temp)
            {
                //I'm swapping the positions using a temporary struct, it is easier for me to visualize. This is a bubble sort!
                temporary[j].temp = temps[j].temp;
                temporary[j].city = temps[j].city;
                temps[j].temp = temps[j + 1].temp;
                temps[j].city = temps[j + 1].city;
                temps[j + 1].temp = temporary[j].temp;
                temps[j + 1].city = temporary[j].city;
            }
        }
    }
    return;
}
