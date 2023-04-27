#include "main.h"

/**
  *get_btn - gets function to handle builtins
  *@cmnd: command
  *)
  *Return: pointer to function
  */
int (*get_btn(char *cmnd))(cmd_in *)
{
	builtin_c builtin[] = {
		{"exit", exit_shell},
		{"env", _env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _changedir},
		{"alias", _makealias},
		{"DO_NIL", _nothing},
		{NULL, NULL}
	};
	int i = 0;

	for (i = 0; i < 7; ++i)
	{
		if (_strcmp(builtin[i].cmd, cmnd) == 0)
			return (builtin[i].btn);
	}
	return (NULL);
}

/**
  *get_path - gets path to an external command
  *@cmd: struct holding important data
  *)
  *Return: full path
  */
char *get_path(cmd_in *cmd)
{
	int i = 0, len;
	char *path = NULL;

	while (cmd->env[i] != NULL)
	{
		if ((_strncmp(cmd->env[i], "PATH=", 5)) == 0)
		{
			len = _strlen(cmd->env[i]);
			path = malloc(sizeof(char) * (len + 1));
			if (path == NULL)
			{
				write(STDERR_FILENO, "Allocation Error\n", 17);
				return (NULL);
			}
			path = _strcpy(path, cmd->env[i]);
			break;
		}
		++i;
	}
	return (path);
}

/**
  *get_alias - gets the alias to an external command
  *@path: the path
  *@arg: the command
  *)
  *Return: alias
  */
char *get_alias(char *path, char *arg)
{
	struct stat st;
	char *alias, *hold, *dir, *slash = "/";

	hold = _strtok(path, "=");
	hold = _strtok(NULL, "=");
	dir = _strtok(hold, ":");
	while (dir != NULL)
	{
		alias = _strdup(dir);
		if (alias == NULL)
			return (NULL);
		alias = _strcat(alias, slash);
		alias = _strcat(alias, arg);
		if (stat(alias, &st) == 0)
		{
			return (alias);
		}
		dir = _strtok(NULL, ":");
		free(alias);
	}
	return (NULL);
}

/**
  *handle_ext - handle external commands
  *@cmd: struct holding important data
  *)
  *Return: 0
  */
int handle_ext(cmd_in *cmd)
{
	struct stat st;
	char *path, *alias;

	if (stat(cmd->args[0], &st) == 0)
	{
		exec(cmd);
		return (0);
	}
	path = get_path(cmd);
	alias = get_alias(path, cmd->args[0]);
	free(path);
	if (alias == NULL)
	{
		_perror(cmd);
		cmd->status = 127;
		return (0);
	}
	free(cmd->cmd);
	cmd->cmd = alias;
	exec(cmd);
	return (0);
}

/**
  *handle_cmd - handles commands given
  *@cmd: struct holding important data
  *)
  *Return: 0
  */
int handle_cmd(cmd_in *cmd)
{
	int (*btn_cmds)(cmd_in *cmd);
	int check;

	check = rep_var(cmd);
	if (check == -1)
		return (0);
	check_alias(cmd);
	free(cmd->cmd);
	cmd->cmd = _strdup(cmd->args[0]);
	btn_cmds = get_btn(cmd->args[0]);
	if (btn_cmds != NULL)
		return (btn_cmds(cmd));
	return (handle_ext(cmd));
}
