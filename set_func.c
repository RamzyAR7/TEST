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

int handle_setenv(char *argv[], char ***environ)
{
	int i = 0;
	char **envp = *environ;
	char buffer[BUFSIZ];

	_strcat(buffer, argv[1]);
	_strcat(buffer, "=");
	_strcat(buffer, argv[2]);

	while (envp[i] != NULL)
	{
		if (_strstr(envp[i], argv[1]) == envp[i] && envp[i][_strlen(argv[1])] == '=')
		{
			free(envp[i]);
			envp[i] = _strdup(buffer);
			arguments_free(argv);
			free_buff(buffer);
			return (0);
		}
		i++;
	}

	add_args(environ, buffer);
	arguments_free(argv);
	free_buff(buffer);
	return (0);
}
void free_buff(char *str)
{
	int i = 0;

	while (str[i])
	{
		str[i] = '\0';
	}
}
