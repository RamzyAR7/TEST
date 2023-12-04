#include "main.h"

int handle_unsetenv(char *argv[], char *envp[])
{
	int i = 0, x = 0;
	printf("before:\n");
	while (envp[i])
	{
		if (_strcmp(envp[i], argv[1]) && envp[i][_strlen(argv[1])] == '=')
		{
			printf("thereenv:\n");
			free(envp[i]);

			x = i;

			while (envp[x])
			{
				envp[x] = envp[x + 1];
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
