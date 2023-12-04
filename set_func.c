#include "main.h"

int handle_env(char *envp[])
{
	int i = 0;

	while (envp[i])
	{
		write(1, envp[i], _strlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
int h_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
int handle_setenv(char *arguments[], char **environ[])
{
	int i = 1, x = 0;
	char **argv = *arguments;
	char buffer[BUFSIZ];

	while (argv[1][i])
	{
		buffer[i] = argv[1][i];
		i++;
	}
	buffer[i++] = '=';
	buffer[i] = '\0';

	while (envp[x])
	{
		if (_strcmp(envp[x], buffer) == 0)
		{
			free(envp[x]);
			_strcat(buffer, argv[2]);

			envp[x] = _strdup(buffer);
			return (0);
		}
		x++;
	}
	_strcat(buffer, argv[2]);

	add_args(envp, buffer);
	return (0);
}
