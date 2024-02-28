#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

unsigned int hash(const char *word);

int main(void)
{
    unsigned int test = hash("alphas");
    //unsigned int max = -1;
    printf("The value of the hash is: %u.\n", test);
    //printf("The value of the max size is: %u.\n")
}

unsigned int hash(const char *word)
{
    int prime_constant = 31;
    unsigned int hash = 0;
    int length = strlen(word);
    for (int i = length - 1; i >= 0; i--)
    {
        hash = (prime_constant * hash) + word[i];
    }
    return hash % 246781;
}
