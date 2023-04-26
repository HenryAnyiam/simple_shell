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
	char *var = _strtok(hold, "$");
	int check;

	var = _strtok(NULL, "\0");
	if (var == NULL)
	{
		free(hold);
		return (0);
	}
	if (_strcmp(var, "$") == 0)
	{
		free(cmd->args[i]);
		cmd->args[i] = _strdup(cmd->pid);
		free(hold);
		return (0);
	}
	if (_strcmp(var, "?") == 0)
	{
		free(cmd->args[i]);
		cmd->args[i] = _itoa(cmd->status);
		free(hold);
		return (0);
	}
	check = saved_var(cmd, var, i);
	if (check == 0)
	{
		free(hold);
		return (0);
	}
	free(cmd->args[i]);
	cmd->args[i] = _strdup("");
	free(hold);
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
