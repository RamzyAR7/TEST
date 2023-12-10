#include "main.h"

/**
 * handle_exit - handles the exit command
 * @arguments: pointer to array of arguments to exit command (char **)
 * Return: 0 if successful, otherwise 1
 * by asraf & ramzy
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
/**
 * checkExitArugment - checks if the argument of exit is valid
 * @str: pointer to argument of exit command (char *)
 * Return: 0 if valid, otherwise 2
 * by asraf & ramzy
*/
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
