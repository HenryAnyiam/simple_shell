#include "main.h"

/**
  *exec - execute command
  *@cmd: struct holding important data
  */
void exec(cmd_in *cmd)
{
	char *er;
	pid_t child;
	int status, check;


	child = fork();
	if (child == -1)
		perror("Child Error");
	else if (child == 0)
	{
		check = execve(cmd->cmd, cmd->args, cmd->env);
		er = _itoa(check);
		write(STDOUT_FILENO, er, _strlen(er));
		fflush(stdout);
		if (check == -1)
			perror(cmd->av[0]);
	}
	else
		wait(&status);
	cmd->status = (status / 256);
}

/**
  *set_args - sets array of ponters containing command line arguments
  *@buf: command line input
  *)
  *Return: array of strings
  */
char **set_args(char *buf)
{
	char *args;
	char *buff, *hold;
	char **argv = malloc(sizeof(char *));
	int i = 0;
	unsigned int temp, temp1;

	args = _strdup(buf);
	buff = _strtok(args, "\n");
	hold = _strtok(buff, " ");
	while (hold != NULL)
	{
		if (hold[0] == '\0')
			hold = _strtok(NULL, " ");
		argv[i] = _strdup(hold);
		hold = _strtok(NULL, " ");
		temp = sizeof(char *) * (i + 1);
		temp1 = sizeof(char *) * (i + 2);
		argv = _realloc(argv, temp, temp1);
		i++;
	}
	argv[i] = NULL;
	free(args);
	return (argv);
}

/**
  *free_cmd - frees an array of pointers
  *@args: array of pointers
  */
void free_cmd(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
  *main - main shell function
  *@ac: argument count
  *@av: array of arguments
  *@env: array of enviroment variables
  *)
  *Return: 0 on success
  */
int main(int __attribute__((unused)) ac, char **av)
{
	cmd_in cmd;

	start_loop(av, &cmd);
	return (cmd.exit);
}
