#include "main.h"

/**
  *_strcpy - copies a string to another
  *@dest: string to be copied to
  *@src: string to be copied from
  (*
  *Return: pointer to copied string
  */
char *_strcpy(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (*(src + i) != '\0')
		++i;
	j = 0;
	while (j <= i)
	{
		dest[j] = src[j];
		++j;
	}
	return (dest);
}
