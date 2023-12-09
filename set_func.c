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
int print_All_Alias(void)
{
	int i = 0;
	char **alias_lisr = Alias_list;

	if (alias_lisr)
		while (alias_lisr[i])
		{
			char *str = _strdup(alias_lisr[i]);
			char *ptr = _strstr(str, "=");
			*ptr = '\0';
			print(STDOUT_FILENO, str, "='", ptr + 1, "'\n", NULL);
			_Free(str);
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
