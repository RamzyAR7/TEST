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

	if (arguments)
	{
		for (i = 0; arguments[i]; i++)
		{
			_Free(arguments[i]);
		}
		_Free(arguments[i]);
		_Free(arguments);
		arguments = NULL;
	}
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
void handle_curCommand(char *first_sigment, char **arguments)
{
	char *c_path;

	if (_strchr(first_sigment, '/') && access(first_sigment, X_OK) == 0)
	{
		c_path = first_sigment;
		handle_exce(c_path, arguments);
		if (State)
			_state(2);
	}
	else if (check_builtin(first_sigment))
	{
		_state(handle_builtin(first_sigment, arguments));
	}
	else
	{
		char *path = get_path(Environment);

		c_path = find_path(path, first_sigment);
		if (c_path)
		{
			handle_exce(c_path, arguments);
			_Free(c_path);
		}
		else
		{
			_state(handle_error(first_sigment, path));
			arguments_free(arguments);
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
 * handle_exit - handles the exit command
 * @arguments: pointer to array of arguments
 * @status: status of the last command
 * Return: 0 if successful, otherwise 1
 * Description: This function is not portable. It will only work on Linux.
 * This function is not portable. It will only work on Linux.
 */
int handle_exit(char **arguments)
{
	int exit_code = _atoi(arguments[1]);
	int check = checkExitArugment(arguments[1]);

	arguments_free(arguments);
	if (check == -1)
	{
		_enviornment(NULL, 0);
		_alias(NULL, 0);
		buffers(NULL, NULL, 0);
		exit(State);
	}
	else if (check == 2)
	{
		return (check);
	}
	else
	{
		_enviornment(NULL, 0);
		_alias(NULL, 0);
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
				print(STDERR_FILENO, error, NULL);
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
int handle_cd(char **arugments)
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
			cd = get_env_value("OLDPWD");
			if (cd)
			{
				_Free(pwd[2]);
				pwd[2] = cd;
				chdir(cd);
				getcwd(cwd, sizeof(cwd));
				print(STDERR_FILENO, cwd, "\n", NULL);
			}
			else
			{
				print(STDERR_FILENO, cwd, "\n", NULL);
				_Free(oldpwd[2]);
				_Free(pwd[2]);
			}
		}
		else
		{
			if (chdir(arugments[1]) == -1)
			{
				if (errno == ENOENT)
				{
					char *error = "./hsh: 1: cd: can't cd to ";

					print(STDERR_FILENO, error, arugments[1], "\n", NULL);
				}
				else if (errno == EACCES)
				{
					char *error = ": Permission denied\n";

					print(STDERR_FILENO, "./hsh: line 1: cd: ", arugments[1], error, NULL);
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
		cd = get_env_value("HOME");
		if (cd)
		{
			_Free(pwd[2]);
			pwd[2] = cd;
			chdir(cd);
		}
	}
	handle_setenv(pwd);
	handle_setenv(oldpwd);
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
	va_end(args);
	array[i] = NULL;
	return (array);
}
int handle_alias(char **arguments)
{
	int state = 0;
	int i = 0;

	if (arguments[1] && arguments[1][0])
	{
		while (arguments[++i])
			if (_strchr(arguments[i], '='))
			{
				_alias(arguments[i], 1);
			}
			else
			{
				state = print_one_Alias(arguments[i]);
			}
	}
	else
	{
		state = print_All_Alias();
	}
	arguments_free(arguments);
	return (state);
}
int print_one_Alias(char *key)
{

	int i = 0;
	char **alias_lisr = Alias_list;

	if (alias_lisr && key)
		while (alias_lisr[i])
		{
			if (_strstr(alias_lisr[i], key) == alias_lisr[i] && alias_lisr[i][_strlen(key)] == '=')
			{
				char *str = _strdup(alias_lisr[i]);
				char *ptr = _strstr(str, "=");
				*ptr = '\0';
				print(STDOUT_FILENO, str, "='", ptr + 1, "'\n", NULL);
				_Free(str);
				return (0);
			}
			i++;
		}
	return (0);
}
