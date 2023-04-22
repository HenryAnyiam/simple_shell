#include "main.h"

/**
  *get_dir - gets a directory from enviroment
  *@cmd: command struct
  *@var: variable to find dir in
  *@len: length of variable
  *)
  *Return: directory or null
  */
char *get_dir(cmd_in *cmd, char *var, int len)
{
	char *temp, *temp1, *dir;
	int i;

	for (i = 0; cmd->env[i] != NULL; i++)
	{
		if ((_strncmp(cmd->env[i], var, len)) == 0)
		{
			temp = _strdup(cmd->env[i]);
			temp1 = _strtok(temp, "=");
			temp1 = _strtok(NULL, "=");
			dir = _strdup(temp1);
			free(temp);
			return (dir);
		}
	}
	return (NULL);
}

/**
  *get_pd - gets the parent directory
  *@cd: current directory
  *)
  *Return: pd or null
  */
char *get_pd(char *cd)
{
	int i, j;
	char *pd;

	if (cd == NULL)
		return (NULL);
	for (i = 0; cd[i] != '\0'; i++)
	{
		if (cd[i] == '/')
			j = i;
	}
	pd = malloc(sizeof(char) * (j + 1));
	if (pd == NULL)
		return (NULL);
	for (i = 0; i < j; i++)
		pd[i] = cd[i];
	pd[i] = '\0';
	return (pd);
}
int cd_dir(cmd_in *cmd, char *new_dir, char *cd)
{
	int i, o, p;

	if (new_dir == NULL)
	{
		cd_perror(cmd);
		return (0);
	}
	i = chdir(new_dir);
	if (i == -1)
	{
		cd_perror(cmd);
		return (0);
	}
	for (i = 0; cmd->env[i] != NULL; i++)
	{
		if (_strncmp(cmd->env[i], "PWD", 3) == 0)
			p = i;
		if (_strncmp(cmd->env[i], "OLDPWD", 6) == 0)
			o = i;
	}
	set_var(cmd, "PWD", new_dir, p);
	set_var(cmd, "OLDPWD", cd, o);
	free(new_dir);
	free(cd);
	return (0);
}
