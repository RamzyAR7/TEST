#include "main.h"
/**
 * handle_exce - handles the excution of command
 * @c_path: pointer to path of command
 * @argumnet: pointer to array of arguments
 * Return: 0 if successful, otherwise 1
 * by asraf & ramzy
 */
int handle_exce(char *c_path, char **argumnet)
{
	int pid = fork();

	if (pid == 0)
	{
		int state = execute_cmd(c_path, argumnet);

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
		if (exit_code)
			_state(2);
		else
			_state(exit_code);
		return (exit_code);
	}
}
/**
 * execute_cmd - executes the command
 * @path: pointer to path of command
 * @args: pointer to array of arguments
 * Return: 0 if successful, otherwise 1
 * by asraf & ramzy
 */
int execute_cmd(char *path, char **args)
{
	execve(path, args, Environment);

	exit(2);
}
/**
 * handle_error - handles the error
 * @first_sigment: pointer to first sigment of command
 * @path: pointer to path of command
 * Return: 0 if successful, otherwise 1
 * by asraf & ramzy
 */
int handle_error(char *first_sigment, char *path)
{
	char error[1024];

	_strcpy(error, "./hsh: line 1: ");
	if (!Environment[0] || !*Environment[0] ||
		_strcmp(Environment[0], "_=") == 0 ||
		!_strchr(Environment[0], '=') || _strlen((char *)Environment) < 5)
	{
		_strcpy(error, "./hsh: 1: ");
		_strcpy(error + _strlen(error), first_sigment);
		print(STDERR_FILENO, error, ": not found\n", NULL);
		return (127);
	}
	_strcpy(error + _strlen(error), first_sigment);
	print(STDERR_FILENO, error, NULL);
	if ((!_strchr(first_sigment, '\\') && path && path[0]) || !path)
	{
		char *error = ": command not found\n";

		print(STDERR_FILENO, error, NULL);
	}
	else
	{
		char *error = ": No such file or directory\n";

		print(STDERR_FILENO, error, NULL);
	}
	return (127);
}
