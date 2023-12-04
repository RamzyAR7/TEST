#ifndef main_h
#define main_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

extern char **environ;
int *_strchr(const char *str, int c);
char *_strtok(char *str, const char *delimiters);
char *_strtok2(char *str, const char *delimiters);
int _strlen(char *p_string);
char *_strdup(char *p_string);
char *_strcpy(char *copy_to, char *copy_from);
int _strcmp(char *string1, char *string2);
int _atoi(char *string);
void *_memcopy(char *copy_to, const char *copy_from, size_t n);
void get_input(char *buff, int *size);
char *get_path(char *envp[]);
char check_many_commands(char *str);
void add_args(char ***arguments_array, char *argument);
int handle_command(char *command, char *path, char **envp, int status);
int execute_cmd(char *path, char **args, char **envp);
char *find_path(char *path, char *input);
int handle_exce(char *c_path, char **argumnet, char **envp);
void arguments_free(char **arguments);
int handle_error(char **envp, char *first_sigment, char *path);
int handle_curCommand(char *first_sigment,
					  char *path, char **arguments, char **envp, int status);
int handle_exit(char **arguments, int status);
int handle_builtin(char *first_sigment, char **arguments,
				   char **envp, int status);
int check_builtin(char *first_sigment);
int checkExitArugment(char *str);
int handle_env(char *envp[]);
int h_env(void);
#endif
