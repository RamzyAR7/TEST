#ifndef main_h
#define main_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *_strchr(const char *str, int c);
char *_strtok(char *str, const char *delimiters);
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
int handle_command(char *command, char *path, char **envp);
int execute_cmd(char *path, char **args, char **envp);
char *find_path(char *path, char *input);

#endif
