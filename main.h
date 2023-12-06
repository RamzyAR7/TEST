#ifndef main_h
#define main_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#define BUFFER_SIZE 255
#define _Free(a) (_free((void *)&(a)))
extern char **environ;
int *_strchr(const char *str, int c);
char *_strtok(char *str, const char *delimiters);
char *_strtok2(char *str, const char *delimiters);
int _strlen(char *p_string);
char *_strdup(char *p_string);
char *_strcpy(char *copy_to, char *copy_from);
int _strcmp(char *string1, char *string2);
int _atoi(char *string);
char *_strcat(char *s1, char *s2);
void *_memcopy(char *copy_to, const char *copy_from, size_t n);
void get_input(char **buff, int *size, int *buffer_size);
void getc_command(char *str, char **c_command, int *cmd_size, int status, char **envp);
char *get_path(char *envp[]);
char check_many_commands(char *str);
void add_args(char ***arguments_array, char *argument);
int handle_command(char *command, char ***envp, int status);
int execute_cmd(char *path, char **args, char **envp);
char *find_path(char *path, char *input);
int handle_exce(char *c_path, char **argumnet, char **envp);
void arguments_free(char **arguments);
int handle_error(char **envp, char *first_sigment, char *path);
int handle_curCommand(char *first_sigment,
					  char **arguments, char ***environ, int status);
int handle_exit(char **arguments, int status, char ***environ);
int handle_builtin(char *first_sigment, char **arguments, char ***environ,
				   int status);
int check_builtin(char *first_sigment);
int checkExitArugment(char *str);
int handle_env(char *envp[]);
int h_env(void);
char **env_dup(char *envp[]);
int handle_setenv(char *argv[], char **environ[]);
void free_buff(char *str);
int handle_unsetenv(char *argv[], char *envp[]);
char *_strstr(char *the_big_str, char *the_little_str);
void handle_str_spaces(char *str, int str_size);
int check_spaces(char *str, int i);
void intail_NULL(char *str, int size);
int handle_cd(char **arugments, char ***environ);
char *get_env_value(char *envp[], char *key);
char **creat_2D(int size, ...);
void edit_command(char **str_ptr, int *str_size, int status, char **envp);
void nts_recursive_helper(int num, char result[], int *index);
void nts(int num, char result[]);
void handle_scape(char *str);
void *_realloc(void *ptr, int new_size);
void buffers(char **all_str, char **c_command, int state);
int empty_text(char *str);
int remove_read_spaces(char *str);
void _free(void **ptr);
#endif
