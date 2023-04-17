#include "main.h"

/**
  *_strlen - counts the length of a string
  *@s: pointer to string
  (*
  *Return: total length
  */
int _strlen(char *s)
{
	int l;

	l = 0;
	while (*(s + l) != '\0')
		++l;
	return (l);
}


/**
  *_strcat - concatenates two strings
  *@dest: strings to be appended to
  *@src: string to append
  *)
  *Return: returns concatenated string
  */
char *_strcat(char *dest, char *src)
{
	int i, j, len;
	char *cat;

	len = _strlen(dest);
	len += _strlen(src);
	cat = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (dest[i] != '\0')
	{
		cat[i] = dest[i];
		++i;
	}
	j = 0;
	while (src[j] != '\0')
	{
		cat[i] = src[j];
		++i;
		++j;
	}
	cat[i] = src[j];
	dest = malloc(sizeof(char) * (len + 1));
	for (i = 0; cat[i] != '\0'; i++)
		dest[i] = cat[i];
	dest[i] = cat[i];
	free(cat);
	return (dest);
}
/**
  *_itoa - converts an integer to a string
  *@i: integer to convert
  *)
  *Return: string equivalent of integer
  */
char *_itoa(int i)
{
	int len = 0, rev = 0;
	char buf[1024];
	char *res;

	if (i == 0)
		return ("0");
	while (i > 0)
	{
		buf[len] = ((i % 10) + '0');
		i /= 10;
		len++;
	}
	res = malloc(sizeof(char) * len);
	len--;
	while (len >= 0)
	{
		res[rev] = buf[len];
		len--;
		rev++;
	}
	res[rev] = '\0';
	return (res);
}


/**
  *_strcmp - compares strings
  *@s1: string to compare
  *@s2: string to be compared with
  *)
  *Return: string difference
  */
int _strcmp(char *s1, char *s2)
{
	int i, j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			j = s1[i] - s2[i];
			break;
		}
		++i;
	}
	if ((j == 0) && (s1[i] != s2[i]))
		j = s1[i] - s2[i];
	return (j);
}

/**
  *_strncmp - compares strings
  *@s1: string to compare
  *@s2: string to be compared with
  *@n: length to compare
  *)
  *Return: string difference
  */
int _strncmp(char *s1, char *s2, int n)
{
	int i, j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			j = s1[i] - s2[i];
			return (j);
		}
		++i;
		if (i == n)
			return (j);
	}
	return (j);
}
