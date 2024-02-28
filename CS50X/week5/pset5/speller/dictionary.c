// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Global variable for size.
int dictionary_size = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 246781; // I describe the reasoning of choosing this below where I comment the hash function!

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the hash, go for the hash place in table, create a pointer to traverse and while pointer is no pointing to null, check if the word is the same as in the dictionary.
    unsigned int hash_code = hash(word);
    node *ptr = table[hash_code];

    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
            // Even though I used tolower for the hash math, I stored the word as is! Important to use strcasecmp here.
        {
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

/*
What I write here is for me to study later and if the staff of CS50 finds this to discover my reasoning for my choices in this solution.

I watched all shorts from Week 5 and also the section and I was a bit intimidated that we should write our own hash function and there was not much content on the subject in CS50.
So I watched a few classes that professor Rob Edwards from San Diego State University on the subject of Hashes in general.
Even though he programs in Java and at this point I've only picked up C from CS50 content, I tried learning conceptually what he teaches.
I've watched all of his eighteen videos on the subject and there are three videos that helped me a lot: "Hashes 2 Hash Function", "Hashes 3 Collision",
"Hashes 4 Hashes Function for Strings" and "Hashes 5 Compressing numbers to fit the size of the array".

The most relevant one (number 4) is the link below:

https://www.youtube.com/watch?v=jtMwp0FqEcg

In this video, professor Rob Edwards explains Hash Functions for strings and he hints (I guess he felt he didn't need to explain to this class in specific)
at two things that "speeds up" computation, even though he writes both of them wrong at the board:

1 - Horner's Method, a way to reduce the number of computations in a polynomial. Basically, instead of doing x = a + bx + cx^2 + d^3 we use x = a + x(b + x(c + dx).
Same result, less computations/number of operations. He writes incorrectly on the board, but only by not writing the obvious way (the first way I wrote value of x),
he already hints that there is a faster way of writing it. I don't know how much time we gain by this, but certainly doing, for example,
6 operations instead of 10 in a vast number of function calls MUST speed things up quite a bit.

2 - Using the position of the character on the string in the computation, such as a way to make two strings that have the same characters
such as "Lana" and "Alan" don't return the same result as hash code. He forgets and he also did the loop starting at zero up to string length,
which would not result in a Horner's Method, but that could be resolved doing by string length minus one down (in a four letter word, strlen would be 4,
but the last char would be word[3]) to zero, zero included (first char would be word[0]).

He also hints the using of prime numbers, and that was already a thought in my mind at this points because of the number of factors are always two in prime numbers (itself and one),
which means that if we use a prime number as a constant for our hash function, the chance of getting a unique value is high.
After researching a bit I learned that apparently primes were discussed as being ideal in hashes ever since the first published work on hashing with chaining.
He uses 31 specifically and this prime used in Java's hashcode for strings. Not only a prime, but a prime that is a Mersenne prime for n = (2^n - 1).
Don't know if it's relevant, but it's cool. Also means that is only one away from 32, and powers of 2 are common in programming, and is also 0b11111 which must be good for bitwise operations,
which are faster then multiplication and other math operations in computing. If my train of thought is of any value, I imagine 127 that is also another Mersenne prime and is represented by 0b1111111 must be another good one for hashing.

Using each character having a power different than the next is a way for removing collision in interchangeable words and the average english word is 5 characters long, so it wouldn't really overflow the integer. In the cases that does,
it would wrap around positive, be divided in the same way. I believe this was a good solution for getting deterministic values, speed and using the buckets. Professor Rob Edwards teaches a bitwise operation for other use cases as well!

Using prime numbers for the array size (number of "buckets") could be a good idea, perhaps the perfect idea if you already know beforehand the size of the data you are loading,
because in an operation of modulo we will always get a number that is a minimum of 0 and a max of the array size minus one tending to be evenly distributed (in other numbers, especially even numbers,
there are a lot of cases that will cause collision because of how common it would be to divide the result by some common factor). In other words, by the very definition a prime number, it only divides evenly by 1 and itself.
So, a relationship between a possible hash function using primes and the array size being a prime will minimize the possibility of collisions (and, by result, increasing the possibility of reducing the number of
operations to search a specific value in the hashtable). However, working with hash tables that you could dinamically alter the size based on the load factor, you would either do something simple such as
duplicate every time the load factor reaches the maximum defined or maybe have a list of primes that you could go up to (could be more trouble than it is worth).

About buckets, I ended up here: https://www.youtube.com/watch?v=B2A2pGrDG8I
This video about the Pigeonhole Principle is made by Brian! Recognize the voice instantly!

For this ocasion, for the load factor I used this as a reference: https://1ykos.github.io/patchmap/#Performance%20comparison
Commonly, the recommended max factor is between 0.6 and 0.75, but this research states that 0.58 could be an ideal number. I don't know if my function really is not colliding, but I tried to optimize.
This is why I chose 246781. 2 - sqrt of 2 * N is aproximate to the dictionary size, so IF my hash function works adequately, it will distribute evenly and be quick.

TLDR: I spent a lot of time on a San Diego State University series of videos on hashes just because I thought this exercise would be hard, but Brian actually makes it quite manageable durint walkthroughs.
The side effect is that a learned a lot about hashes, hash functions, optimization and prime numbers.

*/

// Just to be clear: I wrote this myself after watching the videos from professor Rob Edwards. I explain above. He didn't write this in his classes and he uses Java, but basically is what he recommends (the use of primes, implicitly using Horner's method, etc.).
unsigned int hash(const char *word)
{
    int prime_constant = 31;
    unsigned int hash = 0;
    int length = strlen(word);
    // Maybe without accessing strlen and using pointer arithmetic I could speed up, but I would lose the advantage of Horner's Method because I would need to go up to nul char.
    for (int i = length - 1; i >= 0; i--)
    {
        hash = (prime_constant * hash) + tolower(word[i]);
        //used to lower so the calculations would be the same when checking for words with lowercase. Could be optimized?
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(input, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not create node.\n");
            return false;
        }
        unsigned int hash_code = hash(word);
        strcpy(n->word, word);
        n->next = NULL;
        n->next = table[hash_code];
        table[hash_code] = n;
        dictionary_size++;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size; // Just used global variable that changes every time we insert a new word in the dictionary.
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // After banging my head in pointer on Trie, I guess never again!!!
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}
