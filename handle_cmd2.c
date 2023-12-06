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
					  char **arguments, char ***environ, int status)
{
	char *c_path;
	char **envp = *environ;

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
		status = handle_builtin(first_sigment, arguments, environ, status);
		return (status);
	}
	else
	{
		char *path = get_path(envp);

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
int handle_builtin(char *first_sigment, char **arguments, char ***environ,
				   int status)
{
	char **envp = *environ;

	if (_strcmp(first_sigment, "exit") == 0)
	{
		return (handle_exit(arguments, status, environ));
	}
	else if (_strcmp(first_sigment, "cd") == 0)
	{
		return (handle_cd(arguments, environ));
	}
	else if (_strcmp(first_sigment, "env") == 0)
	{
		arguments_free(arguments);
		return (handle_env(envp));
	}
	else if (_strcmp(first_sigment, "setenv") == 0)
	{
		return (handle_setenv(arguments, environ));
	}
	else if (_strcmp(first_sigment, "unsetenv") == 0)
	{
		return (handle_unsetenv(arguments, envp));
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
int handle_exit(char **arguments, int status, char ***environ)
{
	int exit_code = exit_code = _atoi(arguments[1]);
	int check = checkExitArugment(arguments[1]);

	arguments_free(arguments);
	if (check == -1)
	{
		arguments_free(*environ);
		buffers(NULL, NULL, 0);
		exit(status);
	}
	else if (check == 2)
	{
		return (check);
	}
	else
	{
		arguments_free(*environ);
		buffers(NULL, NULL, 0);
		exit(exit_code);
	}
}
int checkExitArugment(char *str)
{
	int i;

	if (!str || (str && !str[0]))
	{
		return (-1);
	}
	else
	{
		for (i = 0; str[i]; i++)
		{
			if (str[i] < '0' || str[i] > '9')
			{
				char error[1024];

				_strcpy(error, "./hsh: 1: exit: Illegal number: ");
				_strcpy(error + _strlen(error), str);
				_strcpy(error + _strlen(error), "\n");
				write(STDERR_FILENO, error, _strlen(error));
				return (2);
			}
		}
	}
	return (0);
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
int handle_cd(char **arugments, char ***environ)
{
	char cwd[BUFFER_SIZE];
	char *cd = NULL;
	char **pwd;
	char **oldpwd;

	getcwd(cwd, sizeof(cwd));
	pwd = creat_2D(3, "setenv", "PWD", arugments[1]);
	oldpwd = creat_2D(3, "setenv", "OLDPWD", cwd);

	if (arugments[1] && *arugments[1])
	{
		if (_strcmp(arugments[1], "-") == 0)
		{
			cd = get_env_value(*environ, "OLDPWD");

			if (cd)
			{
				free(pwd[2]);
				pwd[2] = cd;
				chdir(cd);
				getcwd(cwd, sizeof(cwd));
				write(STDOUT_FILENO, cwd, _strlen(cwd));
				write(STDOUT_FILENO, "\n", 1);
			}
			else
			{
				char *error = "./hsh: line 1: cd: OLDPWD not set\n";

				write(STDERR_FILENO, error, _strlen(error));
			}
		}
		else
		{
			if (chdir(arugments[1]) == -1)
			{
				if (errno == ENOENT)
				{
					char *error = "./hsh: 1: cd: can't cd to ";

					write(STDERR_FILENO, error, _strlen(error));
					write(STDERR_FILENO, arugments[1], _strlen(arugments[1]));
					write(STDERR_FILENO, "\n", 1);
				}
				else if (errno == EACCES)
				{
					char *error = ": Permission denied\n";

					write(STDERR_FILENO, "./hsh: line 1: cd: ", _strlen("./hsh: line 1: cd: "));
					write(STDERR_FILENO, arugments[1], _strlen(arugments[1]));
					write(STDERR_FILENO, error, _strlen(error));
				}
				arguments_free(pwd);
				arguments_free(oldpwd);
				arguments_free(arugments);
				return (0);
			}
		}
	}
	else
	{
		cd = get_env_value(*environ, "HOME");
		if (cd)
		{
			free(pwd[2]);
			pwd[2] = cd;
			chdir(cd);
		}
		else
		{
			char *error = "./hsh: line 1: cd: HOME not set\n";

			write(STDERR_FILENO, error, _strlen(error));
		}
	}
	handle_setenv(pwd, environ);
	handle_setenv(oldpwd, environ);
	arguments_free(arugments);
	return (0);
}
char **creat_2D(int size, ...)
{
	va_list args;
	char **array = (char **)malloc(sizeof(char *) * (size + 1));
	char *c_argument;
	int i;

	va_start(args, size);
	for (i = 0; i < size; i++)
	{
		c_argument = va_arg(args, char *);
		array[i] = _strdup(c_argument);
	}
	array[i] = NULL;
	return (array);
}
