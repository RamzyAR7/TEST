#include "main.h"

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
int handle_builtin(char *first_sigment, char **arguments)
{

	if (_strcmp(first_sigment, "exit") == 0)
	{
		return (handle_exit(arguments));
	}
	else if (_strcmp(first_sigment, "cd") == 0)
	{
		return (handle_cd(arguments));
	}
	else if (_strcmp(first_sigment, "env") == 0)
	{
		arguments_free(arguments);
		return (handle_env(Environment));
	}
	else if (_strcmp(first_sigment, "setenv") == 0)
	{
		return (handle_setenv(arguments));
	}
	else if (_strcmp(first_sigment, "unsetenv") == 0)
	{
		return (handle_unsetenv(arguments));
	}
	else if (_strcmp(first_sigment, "alias") == 0)
	{
		return (handle_alias(arguments));
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
