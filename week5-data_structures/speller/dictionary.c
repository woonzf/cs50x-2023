// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 2000;

// Size
int entry = 0;

// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    // Load factor should be 0.6 to 0.75 (Occupied buckets / total buckets)
    // Source: Hash table - Wikipedia

    // Load factor = 0.72, total time = 0.12
    // N = 2000, max = 472, min = 1
    int len = strlen(word);
    int n = 0;

    if (len > 1)
    {
        for (int i = 0; i < len; i++)
        {
            if (isalpha(word[i]))
            {
                n += toupper(word[i]);
            }
        }
    }
    else
    {
        n = toupper(word[0]);
    }

    return n % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    // Read strings from file
    char word[LENGTH + 1];

    while (fscanf(inptr, "%s", word) != EOF)
    {
        // Create a new node
        node *w = malloc(sizeof(node));
        if (w == NULL)
        {
            return false;
        }

        strcpy(w->word, word);
        w->next = NULL;

        // Hash word
        int index = hash(w->word);

        // Insert node into hash table
        if (table[index] == NULL)
        {
            table[index] = w;
        }
        else
        {
            w->next = table[index];
            table[index] = w;
        }

        entry++;
    }

    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return entry;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
