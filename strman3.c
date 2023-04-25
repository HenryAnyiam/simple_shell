#include "main.h"

/**
  *rem_spc - checks to remove spaces
  *@str: string to check
  *)
  *Return: new string
  */
char *rem_spc(char *str)
{
	int i, j, len;
	char *new;

	len = _strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	for (i = 0, j = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
		{
			new[j] = str[i];
			j++;
		}
	}
	new[j] = '\0';
	free(str);
	return (new);
}

/**
  *check_args - checks that args don't start with space
  *@cmd: struct holding important data
  */
void check_args(cmd_in *cmd)
{
	int i;

	for (i = 0; cmd->args[i] != NULL; i++)
	{
		cmd->args[i] = rem_spc(cmd->args[i]);
	}
}
