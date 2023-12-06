#include "main.h"
int _read(int fd, char *str, int str_size)
{
	int read_chars = 0;

	read_chars = read(fd, str, str_size);
	if ((str)[read_chars - 1] == '\n')
		(str)[read_chars - 1] = '\0';
	if (read_chars == -1)
	{
		free(str);
		exit(2);
	}
	return (read_chars);
}
void buffers(char **all_str, char **c_command, int state)
{
	static char **str;
	static char **command;

	if (all_str)
		str = all_str;
	if (c_command)
		command = c_command;
	if (state == 0)
	{
		free(*str);
		free(*command);
	}
}
/**
 * get_input - gets input from the user
 * @buff: buffer to store input
 * @size: size of buffer
 * Return: void
 */
void get_input(char **buff, int *size, int *buffer_size)
{
	int n = 1;

	*size = _read(0, *buff, *buffer_size - 1);

	if (*size >= *buffer_size - 1)
		while (*size < *buffer_size - 1)
		{
			*buff = realloc(*buff, *buffer_size * ++n);
			buffers(buff, NULL, 1);
			*size = _read(0, *buff, *buffer_size - 1);
		}
	handle_str_spaces(*buff);
}
/**
 * get_path - gets the PATH variable from the environment
 * @envp: pointer to environment
 * Return: pointer to PATH variable
 * Description: This function is not portable. It will only work on Linux.
 */
char *get_path(char *envp[])
{
	char *path = "PATH=";
	char cur_env[BUFFER_SIZE];
	int i = 0;

	while (envp[i])
	{
		_memcopy(cur_env, envp[i], _strlen(path));
		cur_env[_strlen(path)] = '\0';
		if (_strcmp(path, cur_env) == 0)
		{
			return (envp[i] + _strlen(path));
		}
		i++;
	}
	return (NULL);
}
char *get_env_value(char *envp[], char *key)
{
	char path[BUFFER_SIZE];
	char cur_env[BUFFER_SIZE];
	int i = 0;

	intail_NULL(path, sizeof(path));
	intail_NULL(cur_env, sizeof(cur_env));
	_strcpy(path, key);
	_strcat(path, "=");
	while (envp[i])
	{
		_strcpy(cur_env, envp[i]);
		cur_env[_strlen(path)] = '\0';
		if (_strcmp(path, cur_env) == 0)
		{
			return (_strdup(envp[i] + _strlen(path)));
		}
		i++;
	}
	return (NULL);
}
/**
 * last_space - checks if the last character in a string is a space
 * @str: string to check
 * Return: 1 if last character is a space, otherwise 0
 */
int last_space(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i++] != ' ')
			return (1);
	}
	return (0);
}
/**
 * getc_command - gets the next command from a string
 * @str: string to get command from
 * @c_command: buffer to store command
 * Return: void
 * Description: This function will modify the string passed to it.
 * It will replace the command with 2's and replace spaces with 2's.
 */
void getc_command(char *str, char *c_command, int status, char **envp)
{
	int i = 0, j = 0;

	while (str[i] == 2 || str[i] == ' ')
	{
		i++;
	}
	if (i < BUFFER_SIZE)
		while (str[i])
		{
			if (str[i] == '\n')
			{
				if (str[i + 1] != '\n')
				{
					str[i] = 2;
					break;
				}
				else
				{
					str[i] = 2;
					i++;
				}
			}
			else if (str[i] == ' ' && !last_space(str + i))
			{
				break;
			}
			else if (str[i] == ' ' && str[i + 1] == ' ')
			{
				i++;
				continue;
			}
			else
			{
				c_command[j] = str[i];
				str[i] = 2;
				i++;
				j++;
			}
		}
	c_command[j] = '\0';
	edit_command(c_command, status, envp);
}
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * @envp: array of environment variables
 * Return: 0 if successful, otherwise 1
 */
int main(int argc, char *argv[])
{
	char **envp = env_dup(environ);
	int status = 0;

	argv[argc - 1] = argv[argc - 1];
	while (1)
	{
		char *str = malloc(BUFFER_SIZE);
		char *c_command = malloc(BUFFER_SIZE);
		int read_size;
		int buffer_size = BUFFER_SIZE;
		int command_size = BUFFER_SIZE;

		intail_NULL(str, buffer_size);
		intail_NULL(c_command, command_size);
		get_input(&str, &read_size, &buffer_size);
		buffers(&str, &c_command, 1);
		getc_command(str, c_command, status, envp);
		while (*c_command)
		{
			status = handle_command(c_command, &envp, status);
			getc_command(str, c_command, status, envp);
		}
		if (read_size == 0)
		{
			free(str);
			free(c_command);
			break;
		}
		free(str);
		free(c_command);
	}
	arguments_free(envp);
	if (status)
		exit(status);
	else
		return (status);
}

void handle_str_spaces(char *str)
{
	int i = 0;
	char temp[BUFFER_SIZE];

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

void intail_NULL(char *str, int size)
{
	int i;

	for (i = 0; i < size; i++)
		str[i] = '\0';
}
void edit_command(char *str, int status, char **envp)
{
	int i = 0;
	char temp[BUFFER_SIZE];

	intail_NULL(temp, BUFFER_SIZE);
	for (i = 0; str[i]; i++)
	{
		if (_strcmp(str + i, "$$") == 0)
		{
			char pid[255];

			nts(getpid(), pid);

			_strcpy(temp, str);
			_strcpy(str + i, pid);
			_strcat(str, temp + i + 2);
		}
		else if (_strcmp(str + i, "$?") == 0)
		{
			char last_exit_code[255];

			if (status)
				nts(status, last_exit_code);
			else
				nts(errno, last_exit_code);

			_strcpy(temp, str);
			_strcpy(str + i, last_exit_code);
			_strcat(str, temp + i + 2);
		}
		else if (str[i] == '$' && str[i + 1] != '$' && str[i + 1] != ' ')
		{
			char *value;
			int j = 0;

			while (str[j] && str[j] != ' ')
				j++;

			_memcopy(temp, str + i + 1, ++j);
			temp[j] = '\0';
			value = get_env_value(envp, temp);
			_strcpy(temp, str);
			if (value)
			{
				_strcpy(str + i, value);
				_strcat(str + i + _strlen(value), temp + i + j);
				free(value);
			}
			else
			{
				_strcpy(str + i, temp + i + j + 1);
			}
		}
		else if (str[i] == '#')
		{
			if ((i && str[i - 1] == ' ') || !i)
				str[i] = '\0';
			break;
		}
	}
}
void nts_recursive_helper(int num, char result[], int *index)
{
	if (num < 0)
	{
		result[(*index)++] = '-';
		num = -num;
	}

	if (num / 10 != 0)
	{
		nts_recursive_helper(num / 10, result, index);
	}

	result[(*index)++] = num % 10 + '0';
}

void nts(int num, char result[])
{
	int index = 0;

	nts_recursive_helper(num, result, &index);

	result[index] = '\0';
}
void handle_scape(char *str)
{
	int i = 0;
	char temp[BUFFER_SIZE];

	intail_NULL(temp, BUFFER_SIZE);
	for (i = 0; str[i]; i++)
	{
		if (str[i] == '\\')
		{
			char pid[255];

			nts(getpid(), pid);

			_strcpy(temp, str);
			_strcpy(str + i, temp + i + 1);
		}
	}
}
