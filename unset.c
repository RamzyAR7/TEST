#include "main.h"

int handle_unsetenv(char *argv[], char *envp[])
{
	int i = 0, x = 0;
	while (envp[i])
	{
		if (_strstr(envp[i], argv[1]) == envp[i] && envp[i][_strlen(argv[1])] == '=')
		{
			free(envp[i]);
			envp[i] = envp[i + 1];
			x = i + 1;

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
