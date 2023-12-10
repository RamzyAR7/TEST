#include "main.h"

/**
 * dup_2D - duplicate 2D array of strings (char **)
 * @list: 2D array of strings to duplicate (char **)
 * Return: pointer to new 2D array of strings (char **)
 *
 * by asraf & ramzy
*/
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
/**
 * arguments_free - free 2D array of strings (char **)
 * @arguments: 2D array of strings to free (char **)
 * Return: void
 * Note: sets arguments to NULL after freeing it
 * by asraf & ramzy
*/
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
/**
 * add_args - add argument to 2D array of strings (char **)
 * @arguments_array: 2D array of strings to add argument to (char **)
 * @argument: argument to add to 2D array of strings (char *)
 * Return: void
 * by asraf & ramzy
*/
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
/**
 * creat_2D - create 2D array of strings (char **)
 * @size: size of 2D array of strings to create (int)
 * Return: pointer to new 2D array of strings (char **)
 * Note: last argument must be NULL
 * by asraf & ramzy
*/
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
