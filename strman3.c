#include "main.h"
/**
 * rem_spc - allocates memory for string starting with space 
 * @str: string
 * 
 * Return: new or str
 */
char *rem_spc(char *str)
{
        int i, j, len;
        char *new;

        if (str[0] != ' ')
                return (str);
        len = _strlen(str);
        new = malloc(sizeof(char) * len);
        for (i = 1, j = 0; str[i] != '\0'; i++, j++)
        {
                new[j] = str[i];
        }
        new[j] = '\0';
        free(str);
        return (new);
}
