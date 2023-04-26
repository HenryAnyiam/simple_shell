#include "main.h"

/**
  *remove_comments - removes comments and trailing white spaces
  *@cmd: struct
  *)
  *Return: 0 or -1
  */
int remove_comments(cmd_in *cmd)
{
	char c, a, nil = '\0', sp = ' ';
	int i, len;

	c = cmd->cmd[0];
	a = cmd->cmd[1];
	if (((c <= nil) && (c <= sp)) && ((a == '\0') || (a == '\n')))
		return (-1);
	for (i = 0; cmd->cmd[i] != '\0'; i++)
	{
		c = cmd->cmd[i];
		if (c == '#')
		{
			if (i == 0)
				return (-1);
			strcut(cmd, i);
			break;
		}
		if (cmd->cmd[i + 1] == '\0')
			if (c < 33)
				strcut(cmd, i);
	}
	len = _strlen(cmd->cmd);
	if (len == 0)
		return (-1);
	c = cmd->cmd[len - 1];
	while ((c <= sp) && (c >= nil))
	{
		if ((len - 1) == 0)
			return (-1);
		strcut(cmd, (len - 1));
		len = _strlen(cmd->cmd);
		c = cmd->cmd[len - 1];
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
