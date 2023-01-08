#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

HashTable *NewTable(int size)
{
	HashTable *out = (HashTable *)calloc(1, sizeof(HashTable));

	out->table = (Bin **)calloc(size, sizeof(Bin *));
	out->size = size;

	return out;
}

unsigned int hash(char *word)
{
	unsigned int key = 0;
	while (*word != '\0')
	{
		key = key * HCONST + *word;
		word++;
	}
	return key;
}

void Insert(HashTable *ht, char *word)
{
	unsigned int pos = hash(word) % ht->size;

	Bin *new_bin = (Bin *)calloc(1, sizeof(Bin));

	new_bin->word = (char *)malloc(sizeof(char) * strlen(word) + 1);
	new_bin->next = ht->table[pos];

	ht->table[pos] = new_bin;
	ht->load++;
}

int Get(HashTable *ht, char *word)
{
	unsigned int pos = hash(word) % ht->size;
	Bin *myBin = ht->table[pos];

	while (myBin != NULL)
	{
		if (strcmp(word, myBin->word) == 0)
		{
			return 1;
		}

		myBin = myBin->next;
	}

	return 0;
}

void DeleteTable(HashTable *ht)
{
	for (int i = 0; i < ht->size; i++)
	{
		Bin *myBin = ht->table[i];

		while (myBin != NULL)
		{
			Bin *nextBin = myBin->next;

			free(myBin->word);
			free(myBin);

			myBin = nextBin;
		}
	}

	free(ht);
}