#include "main.h"

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

int set_cmd(cmd_in *cmd, char **arg, int i)
{
	size_t check, size = 0;
	char *buf = NULL;

	check = _getline(&buf, &size, stdin);
	if (check == -1)
	{
		free(buf);
		return (-1);
	}
	if (buf[0] == '\n')
		return (0);
	if (i != 0)
		free_cmd(cmd->args);
	cmd->args = set_args(buf, size);
	free(buf);
	cmd->p = i;
	if (cmd->p == 0)
		cmd->env = cp_env();
	cmd->av = arg;
	cmd->exit = 0;
	return (1);
}

void start_loop(char **arg, cmd_in *cmd)
{
	int check;
	int i = 0;

	while (1)
	{
		write(STDIN_FILENO, "($) ", 4);
		check = set_cmd(cmd, arg, i);
		if (check == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			break;
		}
		else if (check == 0)
			;
		else
		{
			check = handle_cmd(cmd);
			if (check == -1)
			{
				break;
			}
			++i;
		}
	}
	free_cmd(cmd->args);
	free_cmd(cmd->env);
}
