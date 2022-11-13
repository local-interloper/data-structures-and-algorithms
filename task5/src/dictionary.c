#include "dictionary.h"

Dictionary create()
{
    return NULL;
}

void add(Dictionary *dict, char *str)
{

    Word *new_word = (Word *)malloc(sizeof(Word));
    new_word->word = str;
    new_word->count = 1;
    new_word->next = NULL;

    if (*dict == NULL)
    {
        *dict = new_word;
        return;
    }

    Word *current = *dict;

    // First check
    if (strcmp(str, current->word) < 0)
    {
        new_word->next = *dict;
        *dict = new_word;
        return;
    }
    else if (strcmp(str, current->word) == 0)
    {
        current->count++;
        return;
    }

    while (current->next != NULL)
    {
        int result = strcmp(str, current->next->word);
        if (result < 0)
        {
            new_word->next = current->next;
            current->next = new_word;
            return;
        }

        if (result == 0)
        {
            current->next->count++;
            return;
        }

        current = current->next;
    }

    current->next = new_word;
}

void print(Dictionary dict)
{
    Word *current = dict;

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

    Dictionary n_dict = create();
    Word *current = indict;
    for (;;)
    {
        int result = filter(current);

        if (result == 1)
        {
            add(&n_dict, current->word);
        }

        if (current->next == NULL)
        {
            break;
        }

        Word *tmp = current;
        current = current->next;
        free(tmp);
    }

    return n_dict;
}