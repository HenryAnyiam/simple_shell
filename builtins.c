#include "main.h"

/**
  *exit_shell - exits the shell
  *@cmd: struct holding important data
  *)
  *Return: -1
  */
int exit_shell(cmd_in *cmd)
{
	unsigned int i;

	if (cmd->args[1] != NULL)
	{
		if ((_isdigit(cmd->args[1])) == 0)
		{
			i = _atoi(cmd->args[1]);
			if (i > 2147483647)
			{
				_pexit(cmd);
				return (0);
			}
			cmd->status = (i % 256);
		}
		else
		{
			_pexit(cmd);
			return (0);
		}
	}
	return (-1);
}

/**
  *_env - handles the builtin env
  *@cmd: struct holding important data
  *)
  *Return: 0
  */
int _env(cmd_in *cmd)
{
	int i;

	i = 0;
	while (cmd->env[i] != NULL)
	{
		write(STDOUT_FILENO, cmd->env[i], _strlen(cmd->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		++i;
	}
	cmd->status = 0;
	return (0);
}

/**
  *_setenv - handles the builtin setenv
  *@cmd: struct holding important data
  *)
  *Return: 0
  */
int _setenv(cmd_in *cmd)
{
	int i, len_var;

	cmd->status = 0;
	if ((cmd->args[1] == NULL) || (cmd->args[2] == NULL))
	{
		_penv(cmd);
		return (0);
	}
	len_var = _strlen(cmd->args[1]);
	for (i = 0; cmd->env[i] != NULL; i++)
	{
		if ((_strncmp(cmd->env[i], cmd->args[1], len_var)) == 0)
		{
			return (set_var(cmd, cmd->args[1], cmd->args[2], i));
		}
	}
	return (make_var(cmd, i));
}

/**
  *_unsetenv - removes an enviroment variable
  *@cmd: struct holding important data
  *)
  *Return: 0
  */
int _unsetenv(cmd_in *cmd)
{
	int i, len_var;

	cmd->status = 0;
	if (cmd->args[1] == NULL)
	{
		_penv(cmd);
		return (0);
	}
	len_var = _strlen(cmd->args[1]);
	for (i = 0; cmd->env[i] != NULL; i++)
	{
		if ((_strncmp(cmd->env[i], cmd->args[1], len_var)) == 0)
		{
			return (del_var(cmd, i));
		}
	}
	_penv(cmd);
	return (0);
}

/**
  *_changedir - change current directory
  *@cmd: struct holding important data
  *)
  *Return: 0
  */
int _changedir(cmd_in *cmd)
{
	char *home = NULL, *fwd = NULL, *cd = NULL;
	char *pd = NULL, *dir = NULL, *out;

	home = get_dir(cmd, "HOME", 4);
	fwd = get_dir(cmd, "OLDPWD", 6);
	cd = get_dir(cmd, "PWD", 3);
	pd = get_pd(cd);
	if (cmd->args[1] == NULL)
		dir = _strdup(home);
	else if (_strcmp(cmd->args[1], "-") == 0)
	{
		if (fwd == NULL)
			dir = _strdup(cd);
		else
			dir = _strdup(fwd);
		out = _strdup(dir);
		out = _strcat(out, "\n");
		write(STDOUT_FILENO, out, _strlen(out));
		free(out);
	}
	else if (_strncmp(cmd->args[1], "..", 2) == 0)
		dir = mod_str(cmd->args[1], pd, 2);
	else if (_strncmp(cmd->args[1], "~", 1) == 0)
		dir = mod_str(cmd->args[1], home, 1);
	else if (_strncmp(cmd->args[1], ".", 1) == 0)
		dir = mod_str(cmd->args[1], cd, 1);
	else
		dir = _strdup(cmd->args[1]);
	if (pd != NULL)
		free(pd);
	if (fwd != NULL)
		free(fwd);
	if (home != NULL)
		free(home);
	cmd->status = 0;
	return (cd_dir(cmd, dir, cd));
}
