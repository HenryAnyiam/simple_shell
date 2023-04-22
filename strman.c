#include "main.h"

/**
  *_strlen - counts the length of a string
  *@s: pointer to string
  (*
  *Return: total length
  */
int _strlen(const char *s)
{
	int l;

	l = 0;
	while (*(s + l))
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
char *_strcat(char *dest, const char *src)
{
	int i, j, len;
	char *new;

	i = 0;
	while (dest[i] != '\0')
		i++;
	len = _strlen(src) + i;
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
	{
		return (NULL);
	}
	for (i = 0; dest[i] != '\0'; i++)
		new[i] = dest[i];
	j = 0;
	while (src[j])
	{
		new[i] = src[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(dest);
	return (new);
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
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
	{
		return (NULL);
	}
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
