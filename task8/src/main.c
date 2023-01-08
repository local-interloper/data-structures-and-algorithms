#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "hash.h"

int readWord(FILE *fd, char *buffer)
{
	int c;
	
	do {
		c = fgetc(fd);				
		if(c == EOF)
			return 0;
	} while(!isalpha(c));

	do {
		*buffer = c;
		buffer++;
		c = fgetc(fd);
		if(c == 146)
			c = '\'';
	} while(isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

void fillTable(HashTable *dict)
{
	FILE *fd;
	char buffer[1024];
				
	fd = fopen("data/liar.txt", "rt");
	if(fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}
	
	while(readWord(fd, buffer))
	{
		//printf("%s\n", buffer);
		if(!Get(dict, buffer))
			Insert(dict, strdup(buffer));
	}

	fclose(fd);
}

int main()
{
	for(int size = (1<<17); size < (1<<18); size *= 2)
	{
		HashTable *table = NewTable(size);

		float start_time = clock();
		fillTable(table);
		float delta = clock() - start_time;

		printf("Size = %d, load factor = %f, time = %f\n", table->size, (float)table->load / table->size, (delta)/CLOCKS_PER_SEC);

		DeleteTable(table);
	}

	return 0;
}