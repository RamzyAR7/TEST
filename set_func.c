#include "main.h"

char **env_dup(char *envp[])
{
	char **envp2;
	int x = 0, y = 0;

	while (envp[x])
	{
		x++;
	}

	envp2 = malloc(sizeof(envp) * x + 2);

	while (envp[y])
	{
		envp2[y] = malloc(sizeof(envp) *)
			envp2[y] = envp[y];
	}
	envp2[y] = '\0';

	return (envp2);
}
int handle_setenv(char *envp[], char *argv[])
{
	int i = 0;
	char *chank_value;
	char *chank_key;

	while (envp[i])
	{
		chank_key = _strtok(envp[i], "=");
		chank_value = _strtok(NULL, "=");
		if (_strcmp(chank_key, argv[1]) == 0)
		{
			envp[i] = malloc(sizeof(argv[1]) + sizeof(argv[2]) + 2);
			envp[i] = _strcat(argv[1], "=");
			envp[i] = _strcat(envp[i], argv[2]);
			envp[i] = _strcat(envp[i], "\0");
			return (0);
		}
		i++;
	}
	envp[i] = malloc(sizeof(argv[1]) + sizeof(argv[2]) + 3);
	envp[i] = _strcat(argv[1], "=");
	envp[i] = _strcat(envp[i], argv[2]);
	envp[i] = _strcat(envp[i], "\0");
	return (0);
}

int handle_unsetenv(char *envp[], char *argv[])
{
	int i = 0;
	char *chank_key;

	while (envp[i] != NULL)
	{
		chank_key = _strtok(envp[i], "=");
		if (chank_key && _strcmp(chank_key, argv[1]) == 0)
		{
			free(envp[i]);

			while (envp[i] != NULL)
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;

			return (0);
		}
		i++;
	}
}
