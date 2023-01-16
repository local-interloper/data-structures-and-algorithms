#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

// kreira novu hash tablicu (alocira samu strukturu i niz pokazivac
HashTable *NewTable(int size)
{
	HashTable *out = (HashTable *)calloc(1, sizeof(HashTable));

	out->table = (Bin **)calloc(size, sizeof(Bin *));
	out->size = size;

	return out;
}

// od kljuca generira hash kod
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

// dodaje novu rijec u listu na odgovarajucem pretincu
void Insert(HashTable *ht, char *word)
{
	unsigned int pos = hash(word) % ht->size;

	Bin *new_bin = (Bin *)calloc(1, sizeof(Bin));

	new_bin->word = (char *)malloc(sizeof(char) * strlen(word) + 1);
	strcpy(new_bin->word, word);

	new_bin->next = ht->table[pos];

	ht->table[pos] = new_bin;
	ht->load++;
}

// vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici
int Get(HashTable *ht, char *word)
{
	unsigned int pos = hash(word) % ht->size;
	Bin *bin = ht->table[pos];

	while (bin != NULL)
	{
		if (strcmp(word, bin->word) == 0)
		{
			return 1;
		}

		bin = bin->next;
	}

	return 0;
}

// brise cijelu hash tablicu (liste na svim pretincima (rijec i element liste), pretince ...)
void DeleteTable(HashTable *ht)
{
	for (int i = 0; i < ht->size; i++)
	{
		Bin *bin = ht->table[i];

		while (bin != NULL)
		{
			Bin *next_bin = bin->next;

			free(bin->word);
			free(bin);

			bin = next_bin;
		}
	}

	free(ht);
}