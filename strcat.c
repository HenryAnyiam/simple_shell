#include "main.h"

/**
  *_strcat - concatenates two strings
  *@dest: strings to be appended to
  *@src: string to append
  *)
  *Return: returns concatenated string
  */
char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
		++i;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		++i;
		++j;
	}
	dest[i] = src[j];
	return (dest);
}

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
	while(len >= 0)
	{
		res[rev] = buf[len];
		len--;
		rev++;
	}
	res[rev] = '\0';
	return (res);
}
