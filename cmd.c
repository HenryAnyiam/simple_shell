#include "main.h"

int check_cmd(char **arg)
{
	struct stat st;
	int i = 0, len;
	char *path, *hold;
	char *dir = malloc(sizeof(char) * 20);
	char *file = malloc(sizeof(char) * 30);

	if (stat(*arg, &st) == 0)
		return (0);
	while (*(environ + i) != NULL)
	{
		if ((_strncmp(*(environ + i), "PATH=", 5)) == 0)
		{
			len = _strlen(*(environ + i));
			path = malloc(sizeof(char) * (len + 1));
			path = _strcpy(path, *(environ + i));
			break;
		}
		++i;
	}
	hold = malloc(sizeof(char) * (len - 5));
	hold = strtok(path, "=");
	hold = strtok(NULL, "=");
	dir = strtok(hold, ":");
	while (dir != NULL)
	{
		file = _strcat(dir, "/");
		file = _strcat(file, *arg);
		if (stat(file, &st) == 0)
		{
			*arg = malloc(sizeof(char) * (_strlen(file) + 1));
			*arg = _strcpy((*arg), file);
			free(path);
			free(file);
			return (0);
		}
		dir = strtok(NULL, ":");
	}
	free(path);
	free(file);
	return (-1);
}
