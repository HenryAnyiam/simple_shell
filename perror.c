#include "main.h"

/**
  *_perror - prints error on command failure
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
	error = _strcat(error, cmd->cmd);
	error = _strcat(error, ": ");
	error = _strcat(error, "not found\n");
	len = _strlen(error);
	write(STDERR_FILENO, error, len);
	free(error);
	if (cmd->p != 0)
		free(process);
	cmd->status = 2;
}

/**
  *_pexit - prints error on exit failure
  *@cmd: struct holding important data
  */
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
	free(error);
	if (cmd->p != 0)
		free(process);
	cmd->status = 2;
}

/**
  *_penv - prints error on env failure
  *@cmd: struct holding important data
  */
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
	free(error);
	if (cmd->p != 0)
		free(process);
	cmd->status = 2;
}

/**
  *cd_perror - prints error on cd failure
  *@cmd: struct holding important data
  */
void cd_perror(cmd_in *cmd)
{
	char *error;
	int len;
	char *process = _itoa(cmd->p);

	error = _strdup(cmd->av[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, process);
	error = _strcat(error, ": ");
	error = _strcat(error, cmd->args[0]);
	error = _strcat(error, ": Can't cd to ");
	error = _strcat(error, cmd->args[1]);
	error = _strcat(error, "\n");
	len = _strlen(error);
	write(STDERR_FILENO, error, len);
	free(error);
	if (cmd->p != 0)
		free(process);
	cmd->status = 2;
}

/**
  *p_alias - prints error on print alias failure
  *@cmd: struct holding important data
  *@str: alias not found
  */
void p_alias(cmd_in *cmd, char *str)
{
	char *error;
	int len;

	error = _strdup(cmd->args[0]);
	error = _strcat(error, ": ");
	error = _strcat(error, str);
	error = _strcat(error, " not found\n");
	len = _strlen(error);
	write(STDERR_FILENO, error, len);
	free(error);
	cmd->status = 2;
}
