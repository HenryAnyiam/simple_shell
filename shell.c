#include "main.h"

/**
  *_perror - prints error
  *@file: command file
  *@cmd: command
  *@i: process number
  */
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
  */
void exec(char **arg, char **env)
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
  *set_args - sets array of ponters containing command line arguments
  *@buf: command line input
  *@size: length of buffer
  *)
  *Return: struct with array of pointer and size
  */
arg_s set_args(char *buf, int size)
{
	arg_s res;
	char *args = malloc(sizeof(char) * (size + 1));
	char *buff = malloc(sizeof(char) * size);
	char *hold = malloc(sizeof(char) * size);
	char **argv = malloc(sizeof(char *));
	int i = 0, len, temp, temp1;

	args = _strcpy(args, buf);
	buff = strtok(args, "\n");
	hold = strtok(buff, " ");
	while (hold != NULL)
	{
		len = _strlen(hold);
		*(argv + i) = malloc(sizeof(char) * (len + 1));
		*(argv + i) = _strcpy(*(argv + i), hold);
		hold = strtok(NULL, " ");
		temp = sizeof(char *) * (i + 1);
		temp1 = sizeof(char *) * (i + 2);
		argv = _realloc(argv, temp, temp1);
		++i;
	}
	*(argv + i) = NULL;
	res.arg = argv;
	res.size = i + 1;
	free(args);
	return (res);
}

/**
  *free_arg - frees an array of pointers
  *@arg: array of pointers
  */
void free_arg(char **arg)
{
	int i = 0;

	while (arg[i] != NULL)
	{
		free(*(arg + i));
		++i;
	}
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
	char **arg;
	arg_s temp_arg;
	char *buf = NULL;
	size_t check = 0, size = 0;
	int i = 0;

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
			temp_arg = set_args(buf, size);
			arg = malloc((sizeof(char *) * (temp_arg.size)));
			arg = temp_arg.arg;
			if (check_cmd((arg + 0)) == 0)
				exec(arg, env);
			else
				_perror(av[0], arg[0], i);
			++i;
		}
	}
	if (*(arg + 0) != NULL)
	{
		free_arg(arg);
		free(arg);
	}
	return (0);
}
