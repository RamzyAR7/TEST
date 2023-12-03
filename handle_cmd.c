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
	int i = 0, j = 0;
	char **temp;

	while (*arguments_array && (*arguments_array)[i])
		i++;

	temp = (char **)malloc((i + 2) * sizeof(char *));

	for (j = 0; j < i; j++)
	{
		temp[j] = (char *)malloc(_strlen((*arguments_array)[j]) + 1);
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
int handle_command(char *command, char *path, char **envp, int status)
{
	char *first_sigment = _strtok(command, " ");
	char **arguments = NULL;

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
			char c = check_many_commands(cur_sigment);

			if (c)
			{
				if (c == ';')
				{
					cur_sigment[_strlen(cur_sigment) - 1] = '\0';
					add_args(&arguments, cur_sigment);
					status = handle_curCommand(first_sigment, path, arguments, envp);
				}
				else if (c == '&')
				{
					status = handle_curCommand(first_sigment, path, arguments, envp);
					if (status)
						return (status);
				}
				else
				{
					status = handle_curCommand(first_sigment, path, arguments, envp);
				}
			}
			else
			{

				add_args(&arguments, cur_sigment);
			}
		}
	}
	return (handle_curCommand(first_sigment, path, arguments, envp));
}
void handle_exce(char *c_path, char **argumnet, char **envp)
{
	int pid = fork();

	if (pid == 0)
	{
		int state = execute_cmd(c_path, argumnet, envp);

		if (state == -1)
		{
			printf("exError\n");
		}
	}
	else
	{
		int exit_code, i;

		wait(&exit_code);
		if (exit_code != 0)
		{
			printf("there is an error:%d\n", exit_code);
		}
		for (i = 0; argumnet[i]; i++)
		{
			free(argumnet[i]);
		}
		free(argumnet[i]);
		free(argumnet);
	}
}

int handle_error(char **envp, char *first_sigment, char *path)
{
	char error[1024];

	_strcpy(error, "./hsh: line 1: ");
	if (_strchr(envp[0], '%') || !_strchr(envp[0], '='))
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

void arguments_free(char **arguments)
{
	int i;

	for (i = 0; arguments[i]; i++)
	{
		free(arguments[i]);
	}
	free(arguments[i]);
	free(arguments);
	arguments = NULL;
}
int handle_curCommand(char *first_sigment,
					  char *path, char **arguments, char **envp)
{
	char *c_path;

	if (_strchr(first_sigment, '/') && access(first_sigment, X_OK) == 0)
	{
		c_path = first_sigment;
		handle_exce(c_path, arguments, envp);
		return (0);
	}
	else
	{
		c_path = find_path(path, first_sigment);
		if (c_path)
		{
			handle_exce(c_path, arguments, envp);
			free(c_path);
			return (0);
		}
		else
		{
			arguments_free(arguments);
			return (handle_error(envp, first_sigment, path));
		}
	}
}
