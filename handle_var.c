#include "main.h"

/**
  *rep_var - handles variable replacement
  *@cmd: struct holding important data
  *)
  *Return: 0
  */
int rep_var(cmd_in *cmd)
{
	int i, j, check, mark = 0;
	char *hold, *temp, c;

	for (i = 0; cmd->args[0][i] != '\0'; i++)
		if (cmd->args[0][i] == '=')
		{
			hold = _strdup(cmd->args[0]);
			temp = _strtok(hold, "=");
			check = valid_var(temp);
			free(hold);
			if (check == -1)
			{
				_perror(cmd);
				return (-1);
			}
			else
			{
				c = cmd->args[0][i + 1];
				if ((c == '\"') || (c == '\''))
					mark = 1;
				return (create_var(cmd, mark));
			}
		}
	check = 0;
	for (i = 0; cmd->args[i] != NULL; i++)
		for (j = 0; cmd->args[i][j] != '\0'; j++)
		{
			c = cmd->args[i][j];
			if ((c == '"') || (c == '\''))
				check += 1;
			if (check == 2)
				check = 0;
			if ((c == '$') && (check == 0))
			{
				add_variable(cmd, i);
				break;
			}
		}
	return (0);
}

/**
  *create_var - creates a new variable
  *@cmd: struct holding important data
  *@mark: if var in string
  *)
  *Return: 0
  */
int create_var(cmd_in *cmd, int mark)
{
	int j, i = 0, check = 0;
	char c;
	char *var = _strdup(cmd->args[0]);

	if (mark == 1)
	{
		for (i = 0; cmd->args[i] != NULL; i++)
		{
			for (j = 0; cmd->args[i][j] != '\0'; j++)
			{
				c = cmd->args[i][j];
				if ((c == '"') || (c == '\''))
					check += 1;
			}
			if (check == 2)
				break;
		}
		j = 1;
		while ((j <= i) &&  (cmd->args[j] != NULL))
		{
			var = _strcat(var, " ");
			var = _strcat(var, cmd->args[j]);
			j++;
		}
	}
	save_var(cmd, var);
	if (cmd->args[i + 1] != NULL)
	{
		i++;
		return (reset_args(cmd, i));
	}
	return (-1);
}

/**
  *save_var - saves variable
  *@cmd: struct
  *@str: string
  *)
  *Return: 0
  */
int save_var(cmd_in *cmd, char *str)
{
	int i = 0;
	char *var = _strdup(_strtok(str, "="));
	char *val = _strdup(_strtok(NULL, "\0"));
	char *new;

	free(str);
	for (i = 0; cmd->env[i] != NULL; i++)
	{
		if (_strncmp(cmd->env[i], var, _strlen(var)) == 0)
		{
			var = _strcat(var, "=");
			new = rem_slash(val);
			var = _strcat(var, new);
			free(cmd->env[i]);
			cmd->env[i] = var;
			free(val);
			free(new);
		}
	}

	if (cmd->var == NULL)
	{
		cmd->var = malloc(sizeof(char *) * 2);
		cmd->val = malloc(sizeof(char *) * 2);
		cmd->var[0] = var;
		cmd->val[0] = val;
		cmd->var[1] = NULL;
		cmd->val[1] = NULL;
		return (0);
	}
	for (i = 0; cmd->var[i] != NULL; i++)
		if (_strcmp(cmd->var[i], var) == 0)
		{
			free(cmd->val[i]);
			cmd->val[i] = val;
			free(val);
			return (0);
		}
	assign_var(cmd, var, val, i);
	return (0);
}

/**
  *assign_var - realloc array to hold extra variable
  *@cmd: struct
  *@var: variable
  *@val: value
  *@i: index
  */
void assign_var(cmd_in *cmd, char *var, char *val, int i)
{
	unsigned int temp, temp1;

	temp = sizeof(char *) * (i + 1);
	temp1 = sizeof(char *) * (i + 2);
	cmd->var = _realloc(cmd->var, temp, temp1);
	cmd->val = _realloc(cmd->val, temp, temp1);
	cmd->var[i] = var;
	cmd->val[i] = val;
	cmd->var[i + 1] = NULL;
	cmd->val[i + 1] = NULL;
}

/**
  *reset_args - restructures argumnts
  *@cmd: struct
  *@i: index
  *)
  *Return: 0
  */
int reset_args(cmd_in *cmd, int i)
{
	int j;
	char *new = _strdup(cmd->args[i]);

	for (j = (i + 1); cmd->args[j] != NULL; j++)
	{
		new = _strcat(new, " ");
		new = _strcat(new, cmd->args[j]);
	}
	cmd->args = set_args(new);
	free(new);
	return (0);
}
