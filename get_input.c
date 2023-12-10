#include "main.h"

/**
 * get_input - gets input from the user
 * @buff: buffer to store input
 * @size: size of buffer
 * Return: void
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
