#include "main.h"

/**
  *cp_env - copies the enviroment variable to an array
  *)
  *Return: array
  */
char **cp_env(void)
{
	char **env;
	int i;

	for (i = 0; environ[i] != NULL; i++)
		;
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
	{
		write(STDERR_FILENO, "Allocation error\n", 17);
		return (env);
	}
	for (i = 0; environ[i] != NULL; i++)
	{
		env[i] = _strdup(environ[i]);
		if (env[i] == NULL)
			break;
	}
	env[i] = NULL;
	return (env);
}

/**
  *set_cmd - sets the struct data
  *@cmd: struct to set
  *@arg: array of command line arguments
  *@i: current process count
  *@fd: file descriptor
  *)
  *Return: 0 or -1
  */
int set_cmd(cmd_in *cmd, char **arg, int i, int fd)
{
	size_t size = 0;
	ssize_t cmp = -1, check;
	char *buf = NULL;

	cmd->fd = fd;
	check = _getline(&buf, &size, fd);
	if ((check == cmp) && (i != 0))
	{
		free(buf);
		return (-1);
	}
	if (buf[0] == '\n')
		return (0);
	if (i != 1)
	{
		free_cmd(cmd->args);
		free(cmd->cmd);
	}
	cmd->cmd = buf;
	cmd->p = i;
	if (cmd->p == 1)
	{
		cmd->env = cp_env();
		cmd->av = arg;
		cmd->pid = _itoa(getpid());
		cmd->args = NULL;
		cmd->status = 0;
		cmd->exit = 0;
		cmd->name = NULL;
		cmd->value = NULL;
		cmd->var = NULL;
		cmd->val = NULL;
	}
	return (1);
}

/**
  *start_loop - starts shell
  *@arg: command line arguments
  *@cmd: struct
  *@fd: file descriptor
  */
void start_loop(char **arg, cmd_in *cmd, int fd)
{
	int check;
	int i = 1;

	while (1)
	{
		if (fd == STDIN_FILENO)
			write(STDIN_FILENO, "($) ", 4);
		check = set_cmd(cmd, arg, i, fd);
		if (check == -1)
		{
			write(STDIN_FILENO, "^C\n", 3);
			break;
		}
		else if (check == 0)
			;
		else
		{
			check = remove_comments(cmd);
			if (check == -1)
				continue;
			check = handle_sep(cmd);
			if (check == -1)
			{
				break;
			}
			++i;
		}
	}
	free_all(cmd);
}

/**
  *free_all - handles free for struct
  *@cmd: struct
  */
void free_all(cmd_in *cmd)
{
	free(cmd->cmd);
	if (cmd->name != NULL)
	{
		free_cmd(cmd->name);
		free_cmd(cmd->value);
	}
	if (cmd->var != NULL)
	{
		free_cmd(cmd->var);
		free_cmd(cmd->val);
	}
	free(cmd->pid);
	free_cmd(cmd->args);
	free_cmd(cmd->env);
	if (cmd->fd > 0)
		close(cmd->fd);
}
