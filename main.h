#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

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
  *@args: arguments
  *@env: array of enviroment variables
  *@name: alias
  *@value: values
  *@var: variables
  *@val: values
  *@cmd: command input
  *@pid: process ID
  *@status: status of executed command
  *@p: current process
  *@fd: file descriptor
  *@exit: exit status
  */
typedef struct cmd_input
{
	char **av;
	char **args;
	char **env;
	char **name;
	char **value;
	char **var;
	char **val;
	char *cmd;
	char *pid;
	int status;
	int p;
	int fd;
	unsigned int exit;
} cmd_in;

/**
  *struct builtin_s - struct to handle builtin commands
  *@cmd: command
  *@btn: pointer to function
  */
typedef struct builtin_s
{
	char *cmd;
	int (*btn)(cmd_in *cmd);
} builtin_c;

/**
  *struct split_input - linked list to hold current commands
  *@cmd: current command;
  *@next: pointer to next node
  */
typedef struct split_input
{
	char *cmd;
	struct split_input *next;
} cmd_list;

/**
  *struct seperators - linked list to hold seperators
  *@sep: current seperator
  *@next: pointer to next node
  */
typedef struct seperators
{
	char sep;
	struct seperators *next;
} sep_list;

void exec(cmd_in *cmd);
char *_strcat(char *dest, const char *src);
char *_itoa(int i);
int _strlen(const char *s);
void _perror(cmd_in *cmd);
char **set_args(char *buf);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **__realloc(char **ptr, unsigned int old_size, unsigned int new_size);
void free_cmd(char **arg);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
int handle_cmd(cmd_in *cmd);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *src);
int set_cmd(cmd_in *cmd, char **arg, int i, int fd, int mark);
void start_loop(char **arg, cmd_in *cmd, int fd);
char **cp_env(void);
char *get_path(cmd_in *cmd);
char *get_alias(char *path, char *arg);
int handle_ext(cmd_in *cmd);
int (*get_btn(char *cmnd))(cmd_in *cmd);
int exit_shell(cmd_in *cmd);
int _env(cmd_in *cmd);
ssize_t _getline(char **buffer, size_t *size, int fd);
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
char *rem_spc(char *str);
int handle_sep(cmd_in *cmd);
sep_list *add_sep(sep_list **head, char *str);
sep_list *sep_node(sep_list **head, char c);
cmd_list *add_input(cmd_list **head, char *str);
cmd_list *cmd_node(cmd_list **head, char *str);
void next_cmd(cmd_in *cmd, cmd_list **in_temp, sep_list **sp_temp);
void free_in(cmd_list **head);
void free_sp(sep_list **head);
void check_args(cmd_in *cmd);
int _makealias(cmd_in *cmd);
int _makealias(cmd_in *cmd);
int print_all(cmd_in *cmd);
int print_alias(cmd_in *cmd, char *name);
int set_alias(cmd_in *cmd, char *str);
void get_pair(char **name, char **value, char *str);
void p_alias(cmd_in *cmd, char *name);
int get_full(cmd_in *cmd, int index);
int check_alias(cmd_in *cmd);
char *add_slash(char *str);
char *rem_slash(char *str);
void set_new(cmd_in *cmd, char *str);
int create_var(cmd_in *cmd, int mark);
int rep_var(cmd_in *cmd);
int save_var(cmd_in *cmd, char *var);
int reset_args(cmd_in *cmd, int i);
int add_variable(cmd_in *cmd, int i);
int saved_var(cmd_in *cmd, char *var, int i);
void assign_var(cmd_in *cmd, char *var, char *val, int i);
void free_all(cmd_in *cmd);
int remove_comments(cmd_in *cmd);
void strcut(cmd_in *cmd, int i);
void handle_sigint(int sig);

#endif
