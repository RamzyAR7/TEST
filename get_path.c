#include "main.h"

/**
 * get_path - gets the PATH variable from the environment
 * @envp: pointer to environment
 * Return: pointer to PATH variable
 * Description: This function is not portable. It will only work on Linux.
 * by ashraf & ramzy
 */
char *get_path(char *envp[])
{
	char *path = "PATH=";
	char cur_env[BUFFER_SIZE];
	int i = 0;

	while (envp[i])
	{
		_memcopy(cur_env, envp[i], _strlen(path));
		cur_env[_strlen(path)] = '\0';
		if (_strcmp(path, cur_env) == 0)
		{
			return (envp[i] + _strlen(path));
		}
		i++;
	}
	return (NULL);
}

/**
 * find_path - finds the path to a command
 * @path_i: path to search
 * @input: command to search for in path variable (e.g. ls)
 * Return: pointer to path if found, otherwise NULL
 * by ashraf & ramzy
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
		char *buffer = _malloc(buffer_size);
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
