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
const unsigned int N = 26;

// Hash table
node *table[N];
bool zeroed = false;

// prototypes
void free_node(node *n);
bool insert(char *word, unsigned int key);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // search at hash
    node *n = table[hash(word)];

    char *txt = malloc(LENGTH * sizeof(char) + 1);
    strcpy(txt, word);
    char *dict = malloc(LENGTH * sizeof(char) + 1);

    while (n != NULL)
    {
        strcpy(dict, n->word);

        if (strcasecmp(txt, dict) == 0)
        {
            free(txt);
            free(dict);
            return true;
        }
        n = n->next;
    }
    free(txt);
    free(dict);
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
    // open the dictionary file and check if it exists
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // read each word
    char c;
    while (fread(&c, sizeof(char), 1, dict))
    {

        // check if it is a valid letter
        if (isalpha(c))
        {
            // make a word
            char word[LENGTH + 1];
            int index = 1;
            word[0] = c;

            // read to the word if there is still characters and not new line
            while (fread(&c, sizeof(char), 1, dict) && c != '\n')
            {
                word[index] = c;
                index++;
            }

            word[index] = '\0';

            // insert into hash table
            unsigned int key = hash(word);

            // insert into the hash table
            if (!insert(word, key))
            {
                return false;
            }
        }
    }

    // close the dictionary
    fclose(dict);

    return true;
}

// insert words by key linked list
bool insert(char *word, unsigned int key)
{
    if (!zeroed)
    {
        for (int i = 0; i < N; i++)
        {
            table[i] = NULL;
        }
        zeroed = true;
    }

    // malloc new node
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return false;
    }

    // next of new node head of list
    n->next = table[key];
    strncpy(n->word, word, LENGTH + 1);
    table[key] = n;

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    // iterate over the array
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            counter++;
            n = n->next;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        if (n != NULL)
        {
            free_node(n);
        }
    }
    return true;
}

void free_node(node *n)
{
    // node *current = n;
    if (n->next == NULL)
    {
        free(n);
        return;
    }
    free_node(n->next);
    free(n);
}
