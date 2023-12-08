#include "main.h"

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
				return (0);
			}
			i++;
		}
	return (-1);
}
