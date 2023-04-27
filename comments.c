#include "main.h"

/**
  *remove_comments - removes comments and trailing white spaces
  *@cmd: struct
  *)
  *Return: 0 or -1
  */
int remove_comments(cmd_in *cmd)
{
	char c;
	int i, check = 0;

	for (i = 0; cmd->cmd[i] != '\0'; i++)
	{
		c = cmd->cmd[i];
		if ((c == '\'') || (c == '"'))
		{
			check++;
			if (check == 2)
				check = 0;
		}
		if ((c == '#') && (check == 0))
		{
			if (i == 0)
				return (-1);
			strcut(cmd, i);
			return (0);
		}
	}
	return (0);
}

/**
  *strcut - trims a string to i
  *@cmd: struct
  *@i: index to trim to
  */
void strcut(cmd_in *cmd, int i)
{
	int j;
	char *new;

	new = malloc(sizeof(char) * (i + 1));
	for (j = 0; j < i; j++)
	{
		new[j] = cmd->cmd[j];
	}
	new[j] = '\0';
	free(cmd->cmd);
	cmd->cmd = new;
}
