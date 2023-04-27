#include "main.h"

/**
  *set_var - sets a variable to a new value
  *@cmd: struct with important data
  *@var: variable
  *@val: values
  *@i: variable index
  *)
  *Return: 0
  */
int set_var(cmd_in *cmd, char *var, char *val, int i)
{
	char *new_env;

	if ((val == NULL) || (var == NULL))
		return (0);
	new_env = _strdup(var);
	new_env = _strcat(new_env, "=");
	new_env = _strcat(new_env, val);
	if (new_env == NULL)
	{
		_penv(cmd);
		return (0);
	}
	free(cmd->env[i]);
	cmd->env[i] = _strdup(new_env);
	environ[i] = _strcpy(environ[i], new_env);
	free(new_env);
	return (0);
}

/**
  *make_var - creates a new variable
  *@cmd: struct with important data
  *@i: last index
  *)
  *Return: 0
  */
int make_var(cmd_in *cmd, int i)
{
	char *new_env;
	unsigned int temp, temp1;

	if (valid_var(cmd->args[1]) == -1)
	{
		_penv(cmd);
		return (0);
	}
	new_env = _strdup(cmd->args[1]);
	new_env = _strcat(new_env, "=");
	new_env = _strcat(new_env, cmd->args[2]);
	if (new_env == NULL)
	{
		_penv(cmd);
		return (0);
	}
	temp = sizeof(char *) * (i + 1);
	temp1 = sizeof(char *) * (i + 2);
	cmd->env = _realloc(cmd->env, temp, temp1);
	cmd->env[i] = _strdup(new_env);
	cmd->env[i + 1] = NULL;
	free(new_env);
	return (0);
}

/**
  *del_var - deletes a variable
  *@cmd: struct holding important data
  *@i: variable index
  *)
  *Return: 0
  */
int del_var(cmd_in *cmd, int i)
{
	char **new_env;
	int len, skip;

	for (len = 0; cmd->env[len] != NULL; len++)
		;
	new_env = malloc(sizeof(char *) * (len + 1));
	if (new_env == NULL)
	{
		write(STDERR_FILENO, "Allocation Error\n", 18);
		return (0);
	}
	for (len = 0, skip = 0; cmd->env[skip] != NULL; len++, skip++)
	{
		if (len != i)
			new_env[len] = _strdup(cmd->env[skip]);
		if (len == i)
		{
			skip++;
			new_env[len] = _strdup(cmd->env[skip]);
		}
		if (cmd->env[skip] == NULL)
			break;
	}
	new_env[len] = NULL;
	free_cmd(cmd->env);
	cmd->env = new_env;
	return (0);
}
