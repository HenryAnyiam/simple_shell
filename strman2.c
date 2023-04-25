#include "main.h"

/**
  *_isdigit - checks if a string is of only numbers
  *@s: string to check
  *)
  *Return: 0 or -1
  */
int _isdigit(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (!((s[i] >= '0') && (s[i] <= '9')))
			return (-1);
		++i;
	}
	if (i > 10)
		return (-1);
	return (0);
}

/**
  *_isalpha - checks if an entry is an alphabet
  *@c: alphabet to check
  (*
  *Return: 1 if alphabet, 0 otherwise
  */
int _isalpha(int c)
{
	int u;
	int l;

	u = 'A';
	l = 'a';
	while (u <= 'Z')
	{
		if (c == u)
			return (1);
		++u;
	}
	while (l <= 'z')
	{
		if (c == l)
			return (1);
		++l;
	}
	return (0);
}

/**
  *_digit - checks for digit
  *@c: digit to be checked
  (*
  *Return: 1 if digit, 0 otherwise
  */
int _digit(int c)
{
	int l;
	int val;

	val = 0;
	l = '0';
	while (l <= '9')
	{
		if (c == l)
			val = 1;
		++l;
	}
	return (val);
}

/**
  *valid_var - checks if a string meets variable requirement
  *@s: string to check
  *)
  *Return: 0 or -1
  */
int valid_var(char *s)
{
	int i;

	if (!((s[0] == '_') || (_isalpha(s[0]) == 1)))
		return (-1);
	for (i = 1; s[i] != '\0'; i++)
	{
		if (!((s[i] == '-') || (_isalpha(s[i]) == 1) || (_digit(s[i]) == 1)))
			return (-1);
	}
	return (0);
}

/**
  *mod_str - concatenates two string
  *@str: string to modify
  *@mod: string to modify with
  *@i: index to modify from
  *)
  *Return: modified string
  */
char *mod_str(char *str, char *mod, int i)
{
	int len, j;
	char *dir;

	if ((str == NULL) || (mod == NULL))
		return (NULL);
	len = (_strlen(str) - i) + (_strlen(mod));
	dir = malloc(sizeof(char) * (len + 1));
	if (dir == NULL)
		return (NULL);
	for (j = 0; mod[j] != '\0'; j++)
		dir[j] = mod[j];
	while (str[i] != '\0')
	{
		dir[j] = str[i];
		j++;
		i++;
	}
	dir[j] = '\0';
	return (dir);
}
