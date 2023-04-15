#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void exec(char **arg, char **env, int i);
char *_strcat(char *dest, char *src);
char *_itoa(int i);
int _strlen(char *s);
void _perror(char *file, char *cmd, int i);

#endif
