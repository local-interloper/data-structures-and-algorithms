#include "dictionary.h"

Dictionary create()
{
    Dictionary dict = (Dictionary)malloc(sizeof(Dictionary));
    dict->count = 0;
    dict->word = NULL;
    dict->next = NULL;

    return dict;
}

void add(Dictionary dict, char *str)
{
    Word *head = ((Word *)dict)->next;

    // Check if head is NULL
    if (head == NULL)
    {
        Word *new_word = (Word *)calloc(1, sizeof(Word));
        new_word->word = (char *)malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(new_word->word, str);
        new_word->next = NULL;
        new_word->count = 1;
        ((Word *)dict)->next = new_word;
        return;
    }

    Word *ptr = head;

    // Check for dupes
    while (ptr->next != NULL)
    {
        if (strcmp(ptr->word, str) == 0)
        {
            ptr->count++;
            return;
        }

        ptr = ptr->next;
    }

    // Now we add the new word
    ptr = (Word *)dict;

    Word *new_word = (Word *)calloc(1, sizeof(Word));
    new_word->word = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(new_word->word, str);
    new_word->next = NULL;
    new_word->count = 1;

    while (ptr->next != NULL)
    {
        if (strcmp(ptr->next->word, str) > 0)
        {
            Word *tmp = ptr->next;
            ptr->next = new_word;
            new_word->next = tmp;
            return;
        }

        ptr = ptr->next;
    }

    ptr->next = new_word;
}

void print(Dictionary dict)
{
    Word *current = dict->next;

    while (current != NULL)
    {
        printf("%s %d\n", current->word, current->count);
        current = current->next;
    }
}

void destroy(Dictionary dict)
{
    Word *current = dict;

    while (current->next != NULL)
    {
        Word *tmp = current;
        current = current->next;
        free(tmp);
    }

    free(current);
}

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word *w))
{

    Dictionary new_dict = create();
    Word *last = (Word *)new_dict;

    Word *current = ((Word *)indict)->next;
    for (;;)
    {
        int result = filter(current);

        if (result == 1)
        {
            last->next = current;
            last = last->next;
        }

        if (current->next == NULL)
        {
            break;
        }

        Word *tmp = current;
        current = current->next;
        if (result != 1)
        {
            free(tmp);
        }
    }

    return new_dict;
}