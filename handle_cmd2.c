#include "main.h"
/**
 * arguments_free - frees the arguments
 * @arguments: pointer to array of arguments
 * Return: void
 * Description: This function is not portable. It will only work on Linux.
 * This function is not portable. It will only work on Linux.
 */
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
/**
 * handle_curCommand - handles the current command
 * @first_sigment: pointer to first sigment of command
 * @path: pointer to PATH variable
 * @arguments: pointer to array of arguments
 * @envp: pointer to environment variables
 * @status: status of the last command
 * Return: 0 if successful, otherwise 1
 * Description: This function is not portable. It will only work on Linux.
 * This function is not portable. It will only work on Linux.
 */
int handle_curCommand(char *first_sigment,
					  char *path, char **arguments, char **envp, int status)
{
	char *c_path;

	if (_strchr(first_sigment, '/') && access(first_sigment, X_OK) == 0)
	{
		c_path = first_sigment;
		status = handle_exce(c_path, arguments, envp);
		if (status)
			status = 2;
		return (status);
	}
	else if (check_builtin(first_sigment))
	{
		status = handle_builtin(first_sigment, arguments, envp, status);
		return (status);
	}
	else
	{
		c_path = find_path(path, first_sigment);
		if (c_path)
		{
			status = handle_exce(c_path, arguments, envp);
			free(c_path);
			return (status);
		}
		else
		{
			status = handle_error(envp, first_sigment, path);
			arguments_free(arguments);
			return (status);
		}
	}
}
/**
 * handle_builtin - handles the builtin command
 * @first_sigment: pointer to first sigment of command
 * @arguments: pointer to array of arguments
 * @envp: pointer to environment variables
 * @status: status of the last command
 * Return: 0 if successful, otherwise 1
 * Description: This function is not portable. It will only work on Linux.
 * This function is not portable. It will only work on Linux.
 */
int handle_builtin(char *first_sigment, char **arguments, char **envp,
				   int status)
{

	if (_strcmp(first_sigment, "exit") == 0)
	{
		return (handle_exit(arguments, status));
	}
	else if (_strcmp(first_sigment, "cd") == 0)
	{
		return (0);
	}
	else if (_strcmp(first_sigment, "env") == 0)
	{
		return (_strlen(envp[0]));
	}
	else if (_strcmp(first_sigment, "setenv") == 0)
	{
		return (0);
	}
	else if (_strcmp(first_sigment, "unsetenv") == 0)
	{
		return (0);
	}
	else if (_strcmp(first_sigment, "alias") == 0)
	{
		return (0);
	}
	else if (_strcmp(first_sigment, "help") == 0)
	{
		return (0);
	}
	else
	{
		return (0);
	}
}
/**
 * handle_exit - handles the exit command
 * @arguments: pointer to array of arguments
 * @status: status of the last command
 * Return: 0 if successful, otherwise 1
 * Description: This function is not portable. It will only work on Linux.
 * This function is not portable. It will only work on Linux.
 */
int handle_exit(char **arguments, int status)
{
	int exit_code = _atoi(arguments[1]);

	arguments_free(arguments);
	if (!exit_code && status)
		exit(status);
	exit(exit_code);
	return (_atoi(arguments[1]));
}
/**
 * check_builtin - checks if the command is builtin
 * @first_sigment: pointer to first sigment of command
 * Return: 1 if builtin, otherwise 0
 * Description: This function is not portable. It will only work on Linux.
 * This function is not portable. It will only work on Linux.
 */
int check_builtin(char *first_sigment)
{
	char *arr[] = {"exit", "cd", "env", "setenv", "unsetenv", "alias",
				   "help", NULL};
	int i;

	for (i = 0; arr[i]; i++)
	{
		if (_strcmp(first_sigment, arr[i]) == 0)
			return (1);
	}
	return (0);
}
