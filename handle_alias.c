#include "main.h"

/**
 * handle_alias - handle alias command (char **)
 * @arguments: arguments to handle alias command (char **)
 * Return: 0 on success, 1 on failure
 * by ashraf & ramzy
 */
int handle_alias(char **arguments)
{
	int state = 0;
	int i = 0;

	if (arguments[1] && arguments[1][0])
	{
		while (arguments[++i])
			if (_strchr(arguments[i], '='))
			{
				_alias(arguments[i], 1);
			}
			else
			{
				state = print_one_Alias(arguments[i]);
			}
	}
	else
	{
		state = print_All_Alias();
	}
	arguments_free(arguments);
	return (state);
}
/**
 * print_one_Alias - print one alias
 * @key: key to print (char *)
 * Return: 0 on success, 1 on failure
 * by ashraf & ramzy
 */
int print_one_Alias(char *key)
{

	int i = 0;
	char **alias_lisr = Alias_list;

	if (alias_lisr && key)
		while (alias_lisr[i])
		{
			if (_strstr(alias_lisr[i], key) == alias_lisr[i] &&
				alias_lisr[i][_strlen(key)] == '=')
			{
				char *str = _strdup(alias_lisr[i]);
				char *ptr = _strstr(str, "=");
				*ptr = '\0';
				print(STDOUT_FILENO, str, "='", ptr + 1, "'\n", NULL);
				_Free(str);
				return (0);
			}
			i++;
		}
	return (0);
}
/**
 * get_alias_value - get value of alias
 * @key: key to get value of (char *)
 * Return: value of alias (char *)
 * by ashraf & ramzy
 */
char *get_alias_value(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	char *value = NULL;
	int i = 0;
	char **alias_list = Alias_list;

	if (key && *key && alias_list)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (alias_list[i])
		{
			cur_env = alias_list[i];
			if (_strstr(cur_env, path) == cur_env)
			{
				value = _strdup(cur_env + _strlen(path));
				_Free(path);
				return (value);
			}
			i++;
		}
	}
	_Free(path);
	return (value);
}
/**
 * get_alias_index - get index of alias
 * @key: key to get index of (char *)
 * Return: index of alias (int)
 * by ashraf & ramzy
 */
int get_alias_index(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	int i = 0;
	char **alias_list = Alias_list;

	if (key && *key && alias_list)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (alias_list[i])
		{
			cur_env = alias_list[i];
			if (_strstr(cur_env, path) == cur_env)
			{
				_Free(path);
				return (i);
			}
			i++;
		}
	}
	_Free(path);
	return (-1);
}
/**
 * alias_replace - replace alias in command
 * @str_ptr: pointer to command (char **)
 * @str_size: pointer to size of command (int *)
 * Return: void
 * by ashraf & ramzy
 */
void alias_replace(char **str_ptr, int *str_size)
{
	int i = 0;
	char *temp = _malloc(*str_size);
	char *str = *str_ptr;
	char *value = NULL;

	while (1)
	{
		i = 0;
		while (str[i] && str[i] != ' ')
			i++;
		_memcopy(temp, str, i);
		temp[i] = '\0';
		value = get_alias_value(temp);
		if (value)
		{
			str = replaceTxtInd(str_ptr, value, 0, i - 1);
			_Free(value);
		}
		else
		{
			break;
		}
	}
	_Free(temp);
}
