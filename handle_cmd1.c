#include "main.h"

/**
 *  check_many_commands - checks if the user entered many commands
 * @str: pointer to string
 * Return: ';' if the user entered many commands, otherwise 0
 * Description: This function is not portable. It will only work on Linux.
 */

char check_many_commands(char *str)
{
	if (_strcmp(str, ";") == 0)
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
	int i = 0, j = 0;
	char **temp;

	while (*arguments_array && (*arguments_array)[i])
		i++;

	temp = (char **)malloc((i + 2) * sizeof(char *));
	for (j = 0; j < i; j++)
	{
		temp[j] = (char *)malloc(_strlen((*arguments_array)[j]) + 1);
		_strcpy(temp[j], (*arguments_array)[j]);
		_Free((*arguments_array)[j]);
	}
	temp[i] = (char *)malloc(_strlen(argument) + 1);
	_strcpy(temp[i], argument);

	temp[i + 1] = NULL;

	_Free(*arguments_array);

	*arguments_array = temp;
}
/**
 * handle_command - handles the command entered by the user
 * @command: pointer to command
 * @path: pointer to PATH variable
 * @envp: pointer to environment variables
 * @status: status of the last command
 * Return: 0 if successful, otherwise 1
 */
int handle_command(char *command, char ***envp, int status)
{
	char *first_sigment = _strtok2(command, " \t");
	char **arguments = NULL;

	add_args(&arguments, first_sigment);
	while (first_sigment != NULL)
	{
		char *cur_sigment = _strtok2(NULL, " ");

		if (cur_sigment == NULL)
		{
			break;
		}
		else
		{
			char c = check_many_commands(cur_sigment);

			if (c)
			{
				switch (c)
				{
				case ';':
					status = handle_curCommand(first_sigment, arguments, envp, status);
					break;
				case '&':
					status = handle_curCommand(first_sigment, arguments, envp, status);
					if (status != 0)
						return (status);
					break;
				case '|':
					status = handle_curCommand(first_sigment, arguments, envp, status);
					if (!status)
						return (status);
					break;
				default:
					break;
				}
				arguments = NULL;
				first_sigment = _strtok2(NULL, " ");
				if (!first_sigment)
					return (status);
				add_args(&arguments, first_sigment);
			}
			else
			{
				add_args(&arguments, cur_sigment);
			}
		}
	}
	return (handle_curCommand(first_sigment, arguments, envp, status));
}
/**
 * handle_exce - handles the execution of the command
 * @c_path: pointer to command path
 * @argumnet: pointer to array of arguments
 * @envp: pointer to environment variables
 * Return: 0 if successful, otherwise 1
 */
int handle_exce(char *c_path, char **argumnet, char **envp)
{
	int pid = fork();

	if (pid == 0)
	{
		int state = execute_cmd(c_path, argumnet, envp);

		if (state == -1)
		{
			printf("exError\n");
		}
		return (state);
	}
	else
	{
		int exit_code;

		wait(&exit_code);
		arguments_free(argumnet);
		return (exit_code);
	}
}
/**
 * handle_error - handles the error
 * @envp: pointer to environment variables
 * @first_sigment: pointer to first sigment of command
 * @path: pointer to PATH variable
 * Return: 0 if successful, otherwise 1
 * Description: This function is not portable. It will only work on Linux.
 */
int handle_error(char **envp, char *first_sigment, char *path)
{
	char error[1024];

	_strcpy(error, "./hsh: line 1: ");
	if (!envp[0] || !*envp[0] || _strcmp(envp[0], "_=") == 0 ||
		!_strchr(envp[0], '='))
	{
		_strcpy(error, "./hsh: 1: ");
		_strcpy(error + _strlen(error), first_sigment);
		write(STDERR_FILENO, error, _strlen(error));
		write(STDERR_FILENO, ": not found\n", _strlen(": not found\n"));
		return (127);
	}
	_strcpy(error + _strlen(error), first_sigment);
	write(STDERR_FILENO, error, _strlen(error));
	if ((!_strchr(first_sigment, '\\') && path && path[0]) || !path)
	{
		char *error = ": command not found\n";

		write(STDERR_FILENO, error, _strlen(error));
	}
	else
	{
		char *error = ": No such file or directory\n";

		write(STDERR_FILENO, error, _strlen(error));
	}
	return (127);
}
