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
