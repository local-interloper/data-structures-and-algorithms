#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

int cmp(Word *word){
	return (word->count > 5 && word->count < 10) || strlen(word->word) > 3;
}

/*
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
		printf("%s\n", buffer);
		add(dict, buffer);
	}

	fclose(fd);

	print(dict);
}
*/

int main() {
	Dictionary dict = create();

	add(&dict, "the");
	add(&dict, "the");
	add(&dict, "the");
	add(&dict, "the");
	add(&dict, "the");
	add(&dict, "quick");
	add(&dict, "brown");
	add(&dict, "fox");
	add(&dict, "jumps");
	add(&dict, "over");
	add(&dict, "the");
	add(&dict, "lazy");
	add(&dict, "dog");

	print(dict);
	Dictionary dict_f = filterDictionary(dict, &cmp);

	printf("~~~~~~~~~~~~~~~~~~~\n");
	print(dict_f);


	// printf("%d\n", strcmp("Ceca", "Ana"));

	return 0;
}

