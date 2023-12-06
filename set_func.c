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

int handle_setenv(char *argv[])
{
	int i = 0;
	char *buffer = NULL;

	if (argv && argv[1] && argv[2])
	{
		buffer = malloc(_strlen(argv[1]) + _strlen(argv[2]) + 2);
		_strcpy(buffer, argv[1]);
		_strcat(buffer, "=");
		_strcat(buffer, argv[2]);

		while (Environment[i] != NULL)
		{
			if (_strstr(Environment[i], argv[1]) == Environment[i] && Environment[i][_strlen(argv[1])] == '=')
			{
				free(Environment[i]);
				Environment[i] = buffer;
				arguments_free(argv);
				return (0);
			}
			i++;
		}

		add_args(Environment_ptr, buffer);
		arguments_free(argv);
		free_buff(buffer);
		_Free(buffer);
		return (0);
	}
	else
	{
		arguments_free(argv);
		return (2);
	}
}
void free_buff(char *str)
{
	int i = 0;

	while (str[i])
	{
		str[i] = '\0';
	}
}
