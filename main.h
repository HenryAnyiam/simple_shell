#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* array of pointers to enviroment variables */
extern char **environ;

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

/**
  *struct cmd_input - struct to hold input data
  *@av: array of arguments
  *@arg: arguments
  *@env: array of enviroment variables
  *@p: current process
  *@exit: exit status
  */
typedef struct cmd_input
{
	char **av;
	char **args;
	char **env;
	int p;
	unsigned int exit;
} cmd_in;

typedef struct builtin_s
{
	char *cmd;
	int (*btn)(cmd_in *cmd);
} builtin_c;

void exec(cmd_in *cmd);
char *_strcat(char *dest, const char *src);
char *_itoa(int i);
int _strlen(const char *s);
void _perror(cmd_in *cmd);
char **set_args(char *buf, int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **__realloc(char **ptr, unsigned int old_size, unsigned int new_size);
void free_cmd(char **arg);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
int handle_cmd(cmd_in *cmd);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *src);
int set_cmd(cmd_in *cmd, char **arg, int i);
void start_loop(char **arg, cmd_in *cmd);
char **cp_env(void);
char *get_path(cmd_in *cmd);
char *get_alias(char *path, char *arg);
int handle_ext(cmd_in *cmd);
int (*get_btn(char *cmnd))(cmd_in *cmd);
int exit_shell(cmd_in *cmd);
int _env(cmd_in *cmd);
size_t _getline(char **buffer, size_t *size, FILE *stream);
char *_strtok(char *str, const char *delim);
int _strchr(const char *s, char c);
int _atoi(char *s);
void _pexit(cmd_in *cmd);
int _isdigit(char *s);
int _setenv(cmd_in *cmd);
int set_var(cmd_in *cmd, char *var, char *val, int i);
int make_var(cmd_in *cmd, int i);
void _penv(cmd_in *cmd);
int _digit(int c);
int _isalpha(int c);
int valid_var(char *s);
int _unsetenv(cmd_in *cmd);
int del_var(cmd_in *cmd, int i);
int _changedir(cmd_in *cmd);
int cd_dir(cmd_in *cmd, char *new_dir, char *cd);
char *get_pd(char *cd);
char *get_dir(cmd_in *cmd, char *var, int len);
char *mod_str(char *str, char *mod, int i);
void cd_perror(cmd_in *cmd);

#endif
