#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

int cmp(Word *word){
	return (word->count > 5 && word->count < 10) || strlen(word->word) > 3;
}

int readWord(FILE* fd, char* buffer)
{
	int c;

	do {
		c = fgetc(fd);
		if (c == EOF)
			return 0;
	} while (!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if (c == 146)
			c = '\'';
	} while (isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}


void main()
{
	FILE *fd;
	char buffer[1024];
	Dictionary dict;
				
	fd = fopen("../data/liar.txt", "rt");
	if(fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}

	dict = create();
	while(readWord(fd, buffer))
	{
		// printf("%s\n", buffer);
		add(dict, buffer);
	}

	fclose(fd);

	Dictionary d = filterDictionary(dict, cmp);

	print(dict);
	printf("~~~~~~~~~~\n");
	print(d);

	destroy(d);
}

