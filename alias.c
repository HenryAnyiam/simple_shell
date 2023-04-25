#include "main.h"

/**
  *_makealias - handles the alias command
  *@cmd: struct holding important data
  *)
  *Return: 1
  */
int _makealias(cmd_in *cmd)
{
	int i, j = 0;

	if (cmd->args[1] == NULL)
		return (print_all(cmd));
	for (i = 1; cmd->args[i] != NULL; i++)
	{
		for (j = 0; cmd->args[i][j] != '\0'; j++)
		{
			if (cmd->args[i][j] == '=')
			{
				if (cmd->args[i][j + 1] == '\'')
					i = get_full(cmd, i);
				else
					set_alias(cmd, cmd->args[i]);
				break;
			}
			else if (cmd->args[i][j + 1] == '\0')
				print_alias(cmd, cmd->args[i]);
		}
		if (cmd->args[i] == NULL)
			break;
	}
	return (1);
}

/**
  *get_full - gets the full alias
  *@cmd: struct holding important commands
  *@index: index of start of alias
  *)
  *Return: Index stopped at
  */
int get_full(cmd_in *cmd, int index)
{
	int i, check;
	char *arg = _strdup(cmd->args[index]);

	while (check != 2)
	{
		check = 0;
		index++;
		for (i = 0; arg[i] != '\0'; i++)
		{
			if (arg[i] == '\'')
				check += 1;
		}
		if (check == 2)
			index--;
		if (cmd->args[index] == NULL)
			break;
		if (check != 2)
		{
			arg = _strcat(arg, " ");
			arg = _strcat(arg, cmd->args[index]);
		}
	}
	set_alias(cmd, arg);
	return (index);
}

/**
  *print_all - prints the entire alias list
  *@cmd: struct holding important data
  *)
  *Return: 1
  */
int print_all(cmd_in *cmd)
{
	int len, i = 0;
	char *names;

	if (cmd->name == NULL)
		return (1);
	while (cmd->name[i] != NULL)
	{
		names = _strdup(cmd->name[i]);
		names = _strcat(names, "=");
		names = _strcat(names, cmd->value[i]);
		names = _strcat(names, "\n");
		len = _strlen(names);
		write(STDOUT_FILENO, names, len);
		free(names);
		i++;
	}
	return (1);
}

/**
  *print_alias - prints a single alias
  *@cmd: struct holding important data
  *@name: name of alias
  *)
  *Return: 1
  */
int print_alias(cmd_in *cmd, char *name)
{
	int i = 0, len;
	char *names;

	if (cmd->name == NULL)
	{
		p_alias(cmd, name);
		return (1);
	}
	while (cmd->name[i] != NULL)
	{
		if (_strcmp(cmd->name[i], name) == 0)
		{
			names = _strdup(cmd->name[i]);
			names = _strcat(names, "=");
			names = _strcat(names, cmd->value[i]);
			names = _strcat(names, "\n");
			len = _strlen(names);
			write(STDOUT_FILENO, names, len);
			free(names);
			return (1);
		}
		i++;
	}
	p_alias(cmd, name);
	return (1);
}

/**
  *set_alias - set alias
  *@cmd: struct holding important data
  *@str: string with name-value pair
  *)
  *Return: 1
  */
int set_alias(cmd_in *cmd, char *str)
{
	int temp, temp1, i = 0;
	char *name = NULL, *values = NULL;

	get_pair(&name, &values, str);
	free(str);
	if (cmd->name == NULL)
	{
		cmd->name = malloc(sizeof(char *) * 2);
		cmd->value = malloc(sizeof(char *) * 2);
		cmd->name[0] = name;
		cmd->value[0] = values;
		cmd->name[1] = NULL;
		cmd->value[1] = NULL;
		return (1);
	}
	for (i = 0; cmd->name[i] != NULL; i++)
		if (_strcmp(cmd->name[i], name) == 0)
		{
			free(cmd->value[i]);
			cmd->value[i] = values;
			return (1);
		}
	temp = sizeof(char *) * (i + 1);
	temp1 = sizeof(char *) * (i + 2);
	cmd->name = _realloc(cmd->name, temp, temp1);
	cmd->value = _realloc(cmd->value, temp, temp1);
	cmd->name[i] = name;
	cmd->name[i + 1] = NULL;
	cmd->value[i] = values;
	cmd->value[i + 1] = NULL;
	return (1);
}
