// Implements a dictionary's functionality

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file and check to see if the pointer exists
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }

    // Create a word buffer for fscanf
    char word_buffer[LENGTH + 1];

    // Iterate over the whole file
    while (fscanf(d, "%s", word_buffer) != EOF)
    {
        // Allocate memory for the new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        // Get the hashcode for the word
        int hashcode = hash(word_buffer);

        // Copy over the word
        strcpy(new_node->word, word_buffer);

        // Put the new node into place
        new_node->next = table[hashcode];
        table[hashcode] = new_node;
    }

    if (fscanf(d, "%s", word_buffer) == EOF)
    {
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
