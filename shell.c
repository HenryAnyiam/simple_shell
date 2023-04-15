#include "main.h"

void _perror(char *file, char *cmd, int i)
{
	char *error;
	int len = 0;

	len += _strlen(file);
	len += _strlen(": ");
	len += _strlen(_itoa(i));
	len += _strlen(": ");
	len += _strlen(cmd);
	len += _strlen(": ");
	len += _strlen("not found\n");
	error = malloc(sizeof(char) * len);
	error = _strcat(error, file);
	error = _strcat(error, ": ");
	error = _strcat(error, _itoa(i));
	error = _strcat(error, ": ");
	error = _strcat(error, cmd);
	error = _strcat(error, ": ");
	error = _strcat(error, "not found\n");
	write(STDERR_FILENO, error, len);
	free(error);
}

/**
  *exec - execute command
  *@arg: null terminated array of atring with commands
  *@env: null terminated array of string with enviroment variables
  *@i: process count
  */
void exec(char **arg, char **env, int i)
{
	pid_t child;
	int status;

	child = fork();
	if (child == -1)
		perror("Child Error");
	else if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
			perror("exec error");
	}
	else
		wait(&status);
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
	char *arg[] = {NULL, NULL, NULL};
	char *buf = NULL;
	size_t check = 0, size = 0;
	struct stat st;
	int i;

	i = 0;
	while (1)
	{
		write(STDIN_FILENO, "($) ", 4);
		check = getline(&buf, &size, stdin);
		if (check == -1)
		{
			write(STDIN_FILENO, "\n", 1);
			free(buf);
			break;
		}
		else
		{
			arg[0] = malloc(sizeof(char) * size);
			arg[0] = strtok(buf, "\n");
			if (stat(arg[0], &st) == 0)
				exec(arg, env, i);
			else
				_perror(av[0], arg[0], i);
			++i;
		}
	}
	return (0);
}
