// Implements a dhictionary's functionality
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

unsigned int dict_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 45;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int check_index = hash(word);
    node *cursor = table[check_index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
            return true;
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // No citation required, this was my own idea and a very simple, albeit slightly dumb implementation. For educational purposes, after finishing this problemset I have looked at the hash tables used by others for this problem as well as other speller implementations that greatly improve the speed. I have found this stackoverflow post to be the most enlightening as to the possibilites for improvement: https://stackoverflow.com/questions/71313784/cs50-pset5-speller-optimisation.
    return strlen(word) - 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
        return false;
    char dict_word[LENGTH + 1];
    //Read strings from file
    while (fscanf(dict, "%s", dict_word) != EOF)
    {
        //Create new nodes
        node *n = malloc(sizeof(node));
        if (n == NULL)
            return false;
        n->next = NULL;
        //Copy fscanf result into new node
        strcpy(n->word, dict_word);
        //Call hash funtion and get hash index
        unsigned int hash_index = hash(n->word);
        //Insert node into hash table
        n->next = table[hash_index];
        table[hash_index] = n;
        dict_count++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor2 = table[i];
        while (cursor2 !=NULL)
        {
            node *tmp = cursor2;
            cursor2 = cursor2->next;
            free(tmp);
        }
    }
    return true;
}
