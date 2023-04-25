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

/**
  *_strdup - duplicates a string
  *@src: string to duplicate
  *)
  *Return: pointer to duplicate
  */
char *_strdup(const char *src)
{
	char *dup;
	size_t len, i = 0;

	if (src == NULL)
		return (NULL);
	len = _strlen(src);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < len; i++)
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}

/**
  *_strchr - locates a character in a string
  *@s: string to be searched
  *@c: character to be located
  *)
  *Return: returns 1 if character, else 0
  */
int _strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (1);
		++s;
	}
	if (*s == c)
		return (1);
	return (0);
}

/**
  *_strtok - splits string at point of delimeter
  *@str: string to search for delimeter
  *@delim: delimeter
  *)
  *Return: new string or null
  */
char *_strtok(char *str, const char *delim)
{
	static char *p;
	char *new;

	if (str != NULL)
		p = str;
	if ((str == NULL) && (p == NULL))
		return (NULL);
	new = p;
	if (*new == '\0')
		return (NULL);
	while (*p != '\0')
	{
		if ((_strchr(delim, *p)) != 0)
		{
			*p = '\0';
			++p;
			return (new);
		}
		++p;
	}
	return (new);
}

/**
  *_atoi - converts a string to an integer
  *@s: string to be used
  (*
  *Return: ineger to be returned
  */
int _atoi(char *s)
{
	int i, j;
	unsigned int a;

	i =  0;
	j = 1;
	a = 0;
	while (!(s[i] <= '9' && s[i] >= '0') && (s[i] != '\0'))
	{
		if (s[i] == '-')
			j = -(1);

		i++;
	}
	while (s[i] <= '9' && (s[i] >= '0' && s[i] != '\0'))
	{
		a = (a * 10) + (s[i] - '0');
		++i;
	}
	a = a * j;
	return (a);
}
