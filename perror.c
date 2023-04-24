#include "main.h"

/**
  *_perror - prints error
  *@cmd: struct holding command data
  */
void _perror(cmd_in *cmd)
{
	char *error;
	int len;
	char *process = _itoa(cmd->p);

	error = _strdup(cmd->av[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, process);
	error = _strcat(error, ": ");
	error = _strcat(error, cmd->args[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, "not found\n");
	len = _strlen(error);
	write(STDERR_FILENO, error, len);
/*	free(process);*/
	free(error);
}

void _pexit(cmd_in *cmd)
{
	char *error;
	int len;
	char *process = _itoa(cmd->p);

	error = _strdup(cmd->av[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, process);
	error = _strcat(error, ": ");
	error = _strcat(error, cmd->args[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, "Illegal number: ");
	error = _strcat(error, cmd->args[1]);
	error = _strcat(error, "\n");
	len = _strlen(error);
	write(STDERR_FILENO, error, len);
	free(process);
	free(error);
}

void _penv(cmd_in *cmd)
{
	char *error;
	int len;
	char *process = _itoa(cmd->p);

	error = _strdup(cmd->av[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, process);
	error = _strcat(error, ": ");
	error = _strcat(error, cmd->args[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, "Invalid Argument(s)\n");
	len = _strlen(error);
	write(STDERR_FILENO, error, len);
	free(process);
	free(error);
}

void cd_perror(cmd_in *cmd)
{
	write(STDERR_FILENO, "Cannot change", 13);
}
