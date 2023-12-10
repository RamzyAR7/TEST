#ifndef main_h
#define main_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>
#define BUFFER_SIZE 255
#define Get_state -1024
#define Environment_ptr _enviornment(NULL, 1)
#define Environment (*_enviornment(NULL, 1))
#define Alias_list _alias(NULL, 1)
#define State _state(Get_state)
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
void get_input(char **buff, int *size, int *buffer_size, int source);
void getc_command(char *str, char **c_command, int *cmd_size);
char *get_path(char *envp[]);
char check_many_commands(char *str);
void add_args(char ***arguments_array, char *argument);
void handle_command(char *command);
int execute_cmd(char *path, char **args);
char *find_path(char *path, char *input);
int handle_exce(char *c_path, char **argumnet);
void arguments_free(char **arguments);
int handle_error(char *first_sigment, char *path);
void handle_curCommand(char *first_sigment, char **arguments);
int handle_exit(char **arguments);
int handle_builtin(char *first_sigment, char **arguments);
int check_builtin(char *first_sigment);
int checkExitArugment(char *str);
int handle_env(char *envp[]);
int h_env(void);
char **dup_2D(char *list[]);
int handle_setenv(char *argv[]);
void free_buff(char *str);
int handle_unsetenv(char *argv[]);
char *_strstr(char *the_big_str, char *the_little_str);
void handle_str_spaces(char *str, int str_size);
int check_spaces(char *str, int i);
void intail_NULL(char *str, int size);
int handle_cd(char **arugments);
char *get_env_value(char *key);
char **creat_2D(int size, ...);
void edit_command(char **str_ptr, int *str_size);
void nts_recursive_helper(int num, char result[], int *index);
void nts(int num, char result[]);
void nts_recursive_helper(int num, char result[], int *index);
void handle_scape(char *str);
void *_realloc(void *ptr, int new_size);
void buffers(char **all_str, char **c_command, int state);
int empty_text(char *str);
int remove_read_spaces(char *str);
void _free(void **ptr);
char ***_enviornment(char **envp, int state);
int _state(int c_state);
char *replaceTxtInd(char **str1, char *str2, int startIndex, int endIndex);
int Fsize(char *fname);
int last_space(char *str);
char **_alias(char *alias_arg, int state);
int handle_alias(char **arguments);
int print_All_Alias(void);
int print_one_Alias(char *key);
void alias_replace(char **str_ptr, int *str_size);
char *get_alias_value(char *key);
int get_alias_index(char *key);
void print(int fd, ...);
void *_malloc(unsigned int size);
int _read(int fd, char *str, int str_size);
void remove_read_spaces_helper(char *str, int strSize);
void getc_command_helper(char *str, char **c_command,
						 int *cmd_size, int *i, int *j);
void edit_command_helper(char **str_ptr,
						 char **str, char *temp, int *index);
int handle_command_helper(char *first_sigment, char **arguments, char c);
void check_file_mode(char *filename, int *fd, int *active_mode);
void shell_core(char *symbol, int fd, int active_mode);
int handle_cd_helper(char **arugments, char **pwd,
					 char **oldpwd, char *cd, char *cwd);
#endif
