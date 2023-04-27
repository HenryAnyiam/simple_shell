#include "main.h"

/**
  *add_variable - replaces variable in arguments
  *@cmd: struct
  *@i: index
  *)
  *Return: 0
  */
int add_variable(cmd_in *cmd, int i)
{
	char *hold = _strdup(cmd->args[i]);
	char *var;
	int check;

	if (_strcmp(hold, "$$") == 0)
	{
		free(cmd->args[i]);
		cmd->args[i] = _strdup(cmd->pid);
		free(hold);
		return (0);
	}
	if (_strcmp(hold, "$?") == 0)
	{
		free(cmd->args[i]);
		cmd->args[i] = _itoa(cmd->status);
		free(hold);
		return (0);
	}
	var = cut_var(hold);
	if (var == NULL)
	{
		free(hold);
		return (0);
	}
	check = saved_var(cmd, var, i);
	if (check == 0)
	{
		free(var);
		free(hold);
		return (0);
	}
	free(cmd->args[i]);
	cmd->args[i] = NULL;
	free(hold);
	free(var);
	return (0);
}

/**
  *saved_var - checks for var
  *@cmd: struct
  *@var: variable
  *@i: index
  *)
  *Return: 0
  */
int saved_var(cmd_in *cmd, char *var, int i)
{
	int j, len = _strlen(var);
	char *env, *val;

	for (j = 0; cmd->env[j] != NULL; j++)
	{
		if (_strncmp(cmd->env[j], var, len) == 0)
		{
			env = _strdup(cmd->env[j]);
			val = _strtok(env, "=");
			val = _strtok(NULL, "\0");
			free(cmd->args[i]);
			cmd->args[i] = _strdup(val);
			free(env);
			return (0);
		}
	}
	if (cmd->var == NULL)
		return (-1);
	for (j = 0; cmd->var[j] != NULL; j++)
	{
		if (strcmp(cmd->var[j], var) == 0)
		{
			env = _strdup(cmd->val[j]);
			free(cmd->args[i]);
			cmd->args[i] = rem_slash(env);
			free(env);
			return (0);
		}
	}
	return (-1);
}

/**
  *cut_var - removes the first char
  *@c: string
  *)
  *Return: new copy
  */
char *cut_var(char *c)
{
	int j = 0, i = 1, len = _strlen(c);
	char *a;

	if (len == 1)
		return (NULL);
	a = malloc(sizeof(char) * len);
	while (c[i] != '\0')
	{
		a[j] = c[i];
		i++;
		j++;
	}
	a[j] = '\0';
	return (a);
}
