#include "main.h"
/**
 * execute_cmd - executes a command
 * @path: path to command
 * @args: arguments to command
 * @envp: environment variables
 * Return: 0 if successful, otherwise -1
 */
int execute_cmd(char *path, char **args, char **envp)
{
	execve(path, args, envp);

	exit(2);
}
/**
 * find_path - finds the path to a command
 * @path_i: path to search
 * @input: command to search for in path variable (e.g. ls)
 * Return: pointer to path if found, otherwise NULL
 */
char *find_path(char *path_i, char *input)
{
	char *path, *chank = NULL;

	if (path_i)
	{
		path = _strdup(path_i);
		chank = _strtok(path, ":");
	}
	else
	{
		return (NULL);
	}
	while (chank != NULL && *path_i)
	{
		size_t buffer_size = _strlen(chank) + 1 + _strlen(input) + 1;
		char *buffer = malloc(buffer_size);
		int i = 0, j = 0, x = 0;

		while (chank[j])
		{
			buffer[i] = chank[j];
			i++, j++;
		}
		buffer[i] = '/';
		i++;
		while (input[x])
		{
			buffer[i] = input[x];
			i++, x++;
		}
		buffer[i] = '\0';
		if (access(buffer, X_OK) == 0)
		{
			free(path);
			return (buffer);
		}
		free(buffer);
		chank = _strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}