#include "main.h"

/**
  *get_pair - gets an alias name-value pair
  *@name: pointer to hold name
  *@value: pointer to hold value
  *@str: string to get from
  */
void get_pair(char **name, char **value, char *str)
{
	char *a, *buf = NULL;
	size_t size = 0;
	ssize_t cmp = -1, check;

	a = _strtok(str, "=");
	*name = _strdup(a);
	a = _strtok(NULL, "\0");
	if (a == NULL)
		*value = _strdup("");
	else if ((a[0] == '\'') && (a[1] == '\0'))
	{
		write(STDIN_FILENO, "> ", 2);
		check = _getline(&buf, &size, stdin);
		if (check == cmp)
			*value = _strdup("'\n");
		else
		{
			a = _strdup("'\n");
			a = _strcat(a, buf);
			*value = a;
		}
	}
	else
	{
		if (a[0] != '\'')
			*value = add_slash(a);
		else
			*value = _strdup(a);
	}
	if (size > 0)
		free(buf);
}

/**
  *add_slash - adds the char ' to ends of a string
  *@str: string to edit
  *)
  *Return: modified string
  */
char *add_slash(char *str)
{
	char *a = _strdup("'");
	int len;

	a = _strcat(a, str);
	len = _strlen(a);
	if (a[len - 1] != '\'')
		a = _strcat(a, "'");
	return (a);
}

/**
  *rem_slash - removes the char ' from ends of a string
  *@str: string to edit
  *)
  *Return: modified string
  */
char *rem_slash(char *str)
{
	int i, j, len;
	char *s;

	len = _strlen(str);
	s = malloc(sizeof(char) * (len + 1));

	for (i = 0, j = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != '\'') && (str[i] != '"'))
		{
			s[j] = str[i];
			j++;
		}
	}
	s[j] = '\0';
	return (s);
}

/**
  *check_alias - checks if a command is an alias
  *@cmd: struct holding important details
  *)
  *Return: 1
  */
int check_alias(cmd_in *cmd)
{
	char *new, *arg = _strdup(cmd->args[0]);
	int i, check;

	while (cmd->name != NULL)
	{
		for (i = 0; cmd->name[i] != NULL; i++)
		{
			if (_strcmp(cmd->name[i], cmd->args[0]) == 0)
			{
				new = rem_slash(cmd->value[i]);
				check = i;
				break;
			}
			if (cmd->name[i + 1] == NULL)
				check = -1;
		}
		if (check == -1)
			break;
		set_new(cmd, new);
		if (_strcmp(arg, cmd->args[0]) == 0)
			break;
	}
	free(arg);
	return (1);
}

/**
  *set_new - modifies a command according to its alias
  *@cmd: struct holding important data
  *@new: string with new command
  */
void set_new(cmd_in *cmd, char *new)
{
	int i;

	for (i = 0; cmd->args[i] != NULL; i++)
	{
		if (cmd->args[i + 1] == NULL)
		{
			free_cmd(cmd->args);
			cmd->args = set_args(new);
			free(new);
			break;
		}
		new = _strcat(new, cmd->args[i + 1]);
	}
}
