#include "main.h"

int handle_unsetenv(char *argv[])
{
	int i = 0, x = 0;
	char **environment = Environment;

	if (environment && environment[1])
		while (environment[i])
		{
			if (_strstr(environment[i], argv[1]) == environment[i] && environment[i][_strlen(argv[1])] == '=')
			{
				_Free(environment[i]);
				environment[i] = environment[i + 1];
				x = i + 1;

				while (environment[x])
				{
					environment[x] = environment[x + 1];
					x++;
				}
				return (0);
			}
			i++;
		}
	return (-1);
}
