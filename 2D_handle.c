#include "main.h"

char **dup_2D(char *list[])
{
	int rows = 0, i = 0;
	char **list_dup;

	while (*(list + rows) != NULL)
	{
		rows++;
	}

	list_dup = (char **)malloc(sizeof(char *) * (rows + 1));

	if (list_dup == NULL)
	{
		_Free(list_dup);
	}

	for (i = 0; list[i]; i++)
	{
		list_dup[i] = _strdup(list[i]);
	}
	list_dup[i] = NULL;
	return (list_dup);
}
void arguments_free(char **arguments)
{
	int i;

	if (arguments)
	{
		for (i = 0; arguments[i]; i++)
		{
			_Free(arguments[i]);
		}
		_Free(arguments[i]);
		_Free(arguments);
		arguments = NULL;
	}
}
void add_args(char ***arguments_array, char *argument)
{
	int i = 0, j = 0;
	char **temp;

	while (*arguments_array && (*arguments_array)[i])
		i++;

	temp = (char **)malloc((i + 2) * sizeof(char *));
	for (j = 0; j < i; j++)
	{
		temp[j] = (char *)malloc(_strlen((*arguments_array)[j]) + 1);
		_strcpy(temp[j], (*arguments_array)[j]);
		_Free((*arguments_array)[j]);
	}
	temp[i] = (char *)malloc(_strlen(argument) + 1);
	_strcpy(temp[i], argument);

	temp[i + 1] = NULL;

	_Free(*arguments_array);

	*arguments_array = temp;
}
char **creat_2D(int size, ...)
{
	va_list args;
	char **array = (char **)malloc(sizeof(char *) * (size + 1));
	char *c_argument;
	int i;

	va_start(args, size);
	for (i = 0; i < size; i++)
	{
		c_argument = va_arg(args, char *);
		array[i] = _strdup(c_argument);
	}
	va_end(args);
	array[i] = NULL;
	return (array);
}
