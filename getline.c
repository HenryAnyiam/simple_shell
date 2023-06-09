#include "main.h"

/**
  *_getline - reads a line from stream
  *@buffer: pointer to buffer to hold line
  *@size: pointer to size of buffer
  *@fd: stream to read from
  *)
  *Return: size
  */
ssize_t _getline(char **buffer, size_t *size, int fd)
{
	char curr;
	ssize_t cmp = -1, i;
	size_t len = 0, buff_size = 1024;
	char *buff = malloc(sizeof(char) * buff_size);

	if (buff == NULL)
		return (-1);
	if (fd == STDIN_FILENO)
		fflush(stdin);
	while (1)
	{
		i = read(fd, &curr, 1);
		if ((i <= cmp) || ((len == 0) && (i == 0)))
		{
			free(buff);
			return (-1);
		}
		if ((i == 0) || (curr == '\n'))
		{
			buff[len] = curr;
			buff[len + 1] = '\0';
			break;
		}
		else
		{
			buff[len] = curr;
			len++;
			if (len == buff_size)
			{
				buff = _realloc(buff, buff_size, buff_size * 2);
				buff_size *= 2;
			}
		}
	}
	if (*buffer != NULL)
		free(*buffer);
	*buffer = _strdup(buff);
	*size = len;
	free(buff);
	return (len);
}
