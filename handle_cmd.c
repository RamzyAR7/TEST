#include "main.h"
/**
 *  check_many_commands - checks if the user entered many commands
 * @str: pointer to string
 * Return: ';' if the user entered many commands, otherwise 0
 * Description: This function is not portable. It will only work on Linux.
 */
char check_many_commands(char *str)
{
	if (str[_strlen(str) - 1] == ';')
	{
		return (';');
	}
	else if (_strcmp(str, "&&") == 0)
	{
		return ('&');
	}
	else if (_strcmp(str, "||") == 0)
	{
		return ('|');
	}
	return (0);
}
/**
 * add_args - adds an argument to an array of arguments
 * @arguments_array: pointer to array of arguments
 * @argument: argument to add
 * Return: void
 */
void add_args(char ***arguments_array, char *argument)
{
	int i = 0;
	char **temp;

	while (*arguments_array && (*arguments_array)[i])
		i++;

	temp = (char **)malloc((i + 2) * sizeof(char *));

	for (int j = 0; j < i; j++)
	{
		temp[j] = (char *)malloc(strlen((*arguments_array)[j]) + 1);
		_strcpy(temp[j], (*arguments_array)[j]);
		free((*arguments_array)[j]);
	}
	temp[i] = (char *)malloc(_strlen(argument) + 1);
	_strcpy(temp[i], argument);

	temp[i + 1] = NULL;

	free(*arguments_array);

	*arguments_array = temp;
}
/**
 * handle_command - handles the command entered by the user
 * @command: pointer to command
 * @path: pointer to PATH variable
 * Return: 0 if successful, otherwise 1
 */
int handle_command(char *command, char *path, char **envp)
{
	char *first_sigment = _strtok(command, " ");
	char **arguments = NULL;
	char *path;

	add_args(&arguments, first_sigment);
	while (first_sigment != NULL)
	{
		char *cur_sigment = _strtok(NULL, " ");

		if (cur_sigment == NULL)
		{
			break;
		}
		else
		{
			if (check_many_commands(cur_sigment))
			{
			}
			else
			{

				add_args(&arguments, cur_sigment);
				printf("c:%s\n", arguments[0]);
				printf("c:%s\n", arguments[1]);
			}
		}
	}

	if (_strchr(first_sigment, '/'))
	{
		path = first_sigment;
	}
	else
	{
	}
}
void handle_exce(char *c_path, char **argumnet, char **envp)
{
	int pid = fork();

	if (pid == 0)
	{
		execute_cmd(c_path, argumnet, envp);
	}
	else
	{
		int exit_code;

		wait(&exit_code);
	}
}