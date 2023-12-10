#include "main.h"

/**
 * get_input - get input from user
 * @buff: pointer to buffer to store input (char **)
 * @size: pointer to size of input to be returned (int *)
 * @buffer_size: pointer to size of buffer to be returned (int *)
 * @source: source of input (int)
 * Return: void
 * by ashraf & ramzy
 */
void get_input(char **buff, int *size, int *buffer_size, int source)
{
	int max_read = *buffer_size - 1;
	int read = max_read;
	char *temp = _malloc(max_read + 1);

	intail_NULL(temp, max_read + 1);
	while (read == max_read)
	{
		read = _read(source, temp, max_read);
		*size += remove_read_spaces(temp);

		if (*size > *buffer_size - 1)
		{
			*buff = _realloc(*buff, *size + 1);
			*buffer_size = *size;
		}
		_strcat(*buff, temp);
		buffers(buff, NULL, 1);
	}
	_Free(temp);
	handle_str_spaces(*buff, *buffer_size);
}
/**
 * handle_str_spaces - handle spaces in string
 * @str: string to handle spaces in (char *)
 * @str_size: size of string to handle spaces in (int)
 * Return: void
 * by ashraf & ramzy
 */
void handle_str_spaces(char *str, int str_size)
{
	int i = 0;
	char *temp = _malloc(str_size);

	intail_NULL(temp, BUFFER_SIZE);
	while (str && str[i])
	{
		if (check_spaces(str, i) == 1)
		{
			_strcpy(temp, str);
			str[i] = ' ';
			_strcpy(str + i + 1, temp + i);
		}
		else if (check_spaces(str, i) == 2)
		{
			_strcpy(temp, str);
			str[++i] = ' ';
			_strcpy(str + i + 1, temp + i);
		}
		else if (check_spaces(str, i) == 3)
		{
			_strcpy(temp, str);
			i += 2;
			str[i] = ' ';
			_strcpy(str + i + 1, temp + i);
		}
		i++;
	}
	_Free(temp);
}
/**
 * remove_read_spaces - remove spaces from string
 * @str: string to remove spaces from (char *)
 * Return: size of string after removing spaces (int)
 * by ashraf & ramzy
 */
int remove_read_spaces(char *str)
{
	int strSize = _strlen(str);
	int i = 0;

	while (str[i] == ' ')
		i++;
	if (i)
	{
		if (i == strSize - 2)
		{
			intail_NULL(str, strSize);
			return (0);
		}
		else
		{
			char *ptr = str + i;

			_strcpy(str, ptr);
		}
	}
	remove_read_spaces_helper(str, strSize);
	return (_strlen(str));
}
/**
 * remove_read_spaces_helper - helper function for remove_read_spaces
 * @str: string to remove spaces from (char *)
 * @strSize: size of string to remove spaces from (int)
 * Return: void
 * by ashraf & ramzy
 */
void remove_read_spaces_helper(char *str, int strSize)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			int j = empty_text(str + i + 1);

			if (j)
			{
				char *ptr = str + i + 1;
				char *ptr2 = str + i + j + 1;

				_strcpy(ptr, ptr2);
			}
			else
			{
				char *ptr = str + i;

				strSize = _strlen(str);
				intail_NULL(ptr, strSize);
			}
		}
		i++;
	}
}
/**
 * check_spaces - check if there are spaces in string
 * @str: string to check (char *)
 * @i: index to check from (int)
 * Return:
 * (1) if there is a space before ;,
 * (2) if there is a space after ;,
 * (3) if there is a space before && or ||, (0) otherwise (int)
 * by ashraf & ramzy
 */
int check_spaces(char *str, int i)
{
	if (i && str[i] == ';' && str[i - 1] != ' ')
	{
		return (1);
	}
	else if (str[i] == ';' && str[i + 1] != ' ')
	{
		return (2);
	}
	else if (_strstr(str + i, "&&") == str + i ||
			 _strstr(str + i, "||") == str + i)
	{
		if (i && str[i - 1] != ' ')
			return (1);
		else if (str[i + 2] != ' ')
			return (3);
		else
			return (0);
	}
	else
		return (0);
}
