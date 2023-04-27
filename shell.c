#include "main.h"

/**
  *exec - execute command
  *@cmd: struct holding important data
  */
void exec(cmd_in *cmd)
{
	char *er;
	pid_t child;
	int status = 0, check;


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
		if (hold == NULL)
			continue;
		argv[i] = _strdup(hold);
		hold = _strtok(NULL, " ");
		temp = sizeof(char *) * (i + 1);
		temp1 = sizeof(char *) * (i + 2);
		argv = _realloc(argv, temp, temp1);
		i++;
	}
	argv[i] = NULL;
	if (argv[0] == NULL)
	{
		free_cmd(argv);
		argv = malloc(sizeof(char *) * 2);
		argv[0] = _strdup("DO_NIL");
		argv[1] = NULL;
	}

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
  *)
  *Return: 0 on success
  */
int main(int __attribute__((unused)) ac, char **av)
{
	cmd_in cmd;
	int fd = STDIN_FILENO;
	char *arg = NULL;

	signal(SIGINT, handle_sigint);
	if (av[1] != NULL)
		fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		arg = _strdup(av[0]);
		arg = _strcat(arg, ": 0: Can't open ");
		arg = _strcat(arg, av[1]);
		arg = _strcat(arg, "\n");
		write(STDERR_FILENO, arg, _strlen(arg));
		free(arg);
		return (127);
	}
	start_loop(av, &cmd, fd);
	return (cmd.status);
}

/**
  *handle_sigint - handles ctrl c signal
  *@sig: int
  */
void handle_sigint(int __attribute__ ((unused)) sig)
{
	write(STDOUT_FILENO, "\n($) ", 5);
}
