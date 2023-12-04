#include "main.h"

int handle_unsetenv(char *argv[], char *envp[])
{
	int i = 0, x = 0;

	while (envp[i])
	{
		if (_strcmp(envp[i], argv[1]))
		{
			free(envp[i]);

			x = i;

			while (envp[x])
			{
				envp[x] = envp[x + 1];
				x++;
			}
			return (0);
		}
		i++;
	}
	return (-1);
}