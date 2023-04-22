#include "main.h"

/**
  *exec - execute command
  *@arg: null terminated array of atring with commands
  *@env: null terminated array of string with enviroment variables
  */
void exec(cmd_in *cmd)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
		perror("Child Error");
	else if (child == 0)
	{
		if (execve(cmd->args[0], cmd->args, cmd->env) == -1)
			perror("exec error");
	}
	else
		wait(&status);
}

/**
  *set_args - sets array of ponters containing command line arguments
  *@buf: command line input
  *@size: length of buffer
  *)
  *Return: struct with array of pointer and size
  */
char **set_args(char *buf, int size)
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
  *free_arg - frees an array of pointers
  *@arg: array of pointers
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
int main(int ac, char **av, char **env)
{
	cmd_in cmd;

	start_loop(av, &cmd);
	return (cmd.exit);
}
