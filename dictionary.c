// Implements a dictionary's functionality

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

bool dictionary_is_loaded = false;
int size_of_dictionary = 0;

// Represents a node in a hash table

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table defined
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = NULL;

    int hashcode = hash(word);

    cursor = table[hashcode];

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number, taking the first two letters of the word
unsigned int hash(const char *word)
{
    //
    int first_letter = toupper(word[0]) - 'A';
    int second_letter = toupper(word[1]) - 'A';

    first_letter = first_letter * 26;
    return (first_letter + second_letter);
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

        size();
    }

    if (fscanf(d, "%s", word_buffer) == EOF)
    {
        dictionary_is_loaded = true;
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    if (dictionary_is_loaded == true)
    {
        return size_of_dictionary;
    }

    size_of_dictionary++;

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    for (int j = 0; j < N; j++)
    {
        if (table[j] == NULL)
        {
            return false;
        }
    }

    return true;

}

/*
bool unload(void)
{
    bool success = false;

    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        free_memory(tmp);
    }

    for (int j = 0; j < N; j++)
    {
        if (table[j] == NULL)
        {
            return false;
        }
    }

    return true;
}
*/


/*
void free_memory(node *free_node)
{
    if (free_node->next == NULL)
    {
        return;
    }

    free_memory(free_node->next);

    free(free_node);
}
*/
