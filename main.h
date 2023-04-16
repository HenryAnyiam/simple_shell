#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
  *struct args - struct of arguments
  *@arg: array of strings
  *@size: size of array
  */
typedef struct args
{
	char **arg;
	int size;
} arg_s;

void exec(char **arg, char **env, int i);
char *_strcat(char *dest, char *src);
char *_itoa(int i);
int _strlen(char *s);
void _perror(char *file, char *cmd, int i);
arg_s set_args(char **argv, char *buf, int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_arg(char **arg);

#endif
