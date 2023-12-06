#include "main.h"
int _read(int fd, char *str, int str_size)
{
	int read_chars = 0;

	read_chars = read(fd, str, str_size);
	if ((str)[read_chars - 1] == '\n')
		(str)[read_chars - 1] = '\0';
	if (read_chars == -1)
	{
		_Free(str);
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
		_Free(*str);
		_Free(*command);
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
	int max_read = *buffer_size - 1;
	int read = max_read;
	char *temp = malloc(max_read + 1);

	intail_NULL(temp, max_read + 1);
	while (read == max_read)
	{
		read = _read(0, temp, max_read);
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
char *get_env_value(char *key)
{
	char *path = NULL;
	char *cur_env = NULL;
	char *value = NULL;
	int i = 0;

	if (key && *key)
	{
		path = _strdup(key);
		path = _realloc(path, _strlen(path) + 2);
		_strcat(path, "=");

		while (Environment[i])
		{
			cur_env = Environment[i];
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
void getc_command(char *str, char **c_command, int *cmd_size)
{
	int i = 0, j = 0;

	while (str[i] == 2 || str[i] == ' ')
	{
		i++;
	}
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
			if (j < *cmd_size - 2)
			{
				(*c_command)[j] = str[i];
				str[i] = 2;
				i++;
				j++;
			}
			else
			{
				*c_command = _realloc(*c_command, *cmd_size * 2);
				*cmd_size *= 2;
				buffers(NULL, c_command, 1);
			}
		}
	}
	(*c_command)[j] = '\0';
	edit_command(c_command, cmd_size);
}
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * @envp: array of environment variables
 * Return: 0 if successful, otherwise 1
 */
int main(int argc, char *argv[], char *envp[])
{
	int active_mode = isatty(STDIN_FILENO);

	_enviornment(env_dup(envp), 1);
	argv[argc - 1] = argv[argc - 1];
	do
	{
		char *str = malloc(BUFFER_SIZE);
		char *c_command = malloc(BUFFER_SIZE);
		int read_size = 0;
		int buffer_size = BUFFER_SIZE;
		int command_size = BUFFER_SIZE;

		intail_NULL(str, buffer_size);
		intail_NULL(c_command, command_size);
		get_input(&str, &read_size, &buffer_size);
		buffers(&str, &c_command, 1);
		getc_command(str, &c_command, &command_size);
		while (*c_command)
		{
			handle_command(c_command);

			getc_command(str, &c_command, &command_size);
		}
		if (read_size == 0)
		{
			_Free(str);
			_Free(c_command);
			break;
		}
		_Free(str);
		_Free(c_command);
	} while (active_mode);
	_enviornment(NULL, 0);
	if (State)
		exit(State);
	else
		return (State);
}

void handle_str_spaces(char *str, int str_size)
{
	int i = 0;
	char *temp = malloc(str_size);

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
void edit_command(char **str_ptr, int *str_size)
{
	int i = 0;
	int temp_size = *str_size;
	char *temp = malloc(temp_size);
	char *str = *str_ptr;

	intail_NULL(temp, *str_size);
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

			if (State)
				nts(State, last_exit_code);
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

			while (str[i + j] && str[i + j] != ' ')
				j++;
			_memcopy(temp, str + i + 1, ++j);
			temp[j] = '\0';
			value = get_env_value(temp);

			_strcpy(temp, str);
			if (value)
			{

				if (*str_size - 2 < i + _strlen(value) + _strlen(temp + i + j) + 1)
				{
					*str_ptr = _realloc(str_ptr, i + _strlen(value) + _strlen(temp + i + j) + 2);
					*str_size = i + _strlen(value) + _strlen(temp + i + j) + 2;
					buffers(NULL, str_ptr, 1);
				}
				_strcpy(str + i, value);
				_strcat(str + i + _strlen(value), temp + i + j);
				_Free(value);
			}
			else
			{
				_strcpy(str + i, temp + i + j);
			}
		}
		else if (str[i] == '#')
		{
			if ((i && str[i - 1] == ' ') || !i)
				str[i] = '\0';
			break;
		}
	}
	_Free(temp);
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
char ***_enviornment(char **envp, int state)
{
	static char **enviornment;

	if (state && envp)
	{
		enviornment = envp;
	}
	if (!state)
	{
		arguments_free(enviornment);
	}
	return (&enviornment);
}
int _state(int c_state)
{
	static int state;

	state = c_state;
	if (c_state == Get_state)
	{
		return (state);
	}
	else
	{
		state = c_state;
		return (state);
	}
}
