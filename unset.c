#include "main.h"

int handle_unsetenv(char *argv[])
{
	int i = 0, x = 0;

	if (Environment && Environment[1])
		while (Environment[i])
		{
			if (_strstr(Environment[i], argv[1]) == Environment[i] && Environment[i][_strlen(Environment[1])] == '=')
			{
				free(Environment[i]);
				Environment[i] = Environment[i + 1];
				x = i + 1;

				while (Environment[x])
				{
					Environment[x] = Environment[x + 1];
					x++;
				}
				_enviornment(NULL, 0);
				return (0);
			}
			i++;
		}
	_enviornment(NULL, 0);
	return (-1);
}
