#include "main.h"

int handle_env(char *envp[])
{
	int i = 0;

	while (envp[i])
	{
		print(STDOUT_FILENO, envp[i], "\n", NULL);
		i++;
	}
	return (0);
}
int handle_unsetenv(char *argv[])
{
	int i = 0, x = 0;
	char **env = Environment;

	if (env && argv[1])
		while (env[i])
		{
			if (_strstr(env[i], argv[1]) == env[i] && env[i][_strlen(argv[1])] == '=')
			{
				_Free(env[i]);
				env[i] = env[i + 1];
				x = i + 1;

				while (env[x])
				{
					env[x] = env[x + 1];
					x++;
				}
				arguments_free(argv);
				return (0);
			}
			i++;
		}
	arguments_free(argv);
	return (-1);
}

int handle_setenv(char *argv[])
{
	int i = 0;
	char *buffer = NULL;

	if (argv && argv[1] && argv[2])
	{
		buffer = _malloc(_strlen(argv[1]) + _strlen(argv[2]) + 2);
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
char *get_env_value(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	char *value = NULL;
	int i = 0;
	char **env_list = Environment;

	if (key && *key && env_list)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (env_list[i])
		{
			cur_env = env_list[i];
			if (_strstr(cur_env, path) == cur_env)
			{
				value = _strdup(cur_env + _strlen(path));
				_Free(path);
				return (value);
			}
			i++;
		}
	}
	_Free(path);
	return (value);
}
