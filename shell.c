#include "main.h"
/**
 * get_input - gets input from the user
 * @buff: buffer to store input
 * @size: size of buffer
 * Return: void
 */
void get_input(char *buff, int *size)
{
	*size = read(0, buff, BUFSIZ);
	if (*size == -1)
	{
		exit(2);
	}
	if (buff[*size - 1] == '\n')
		buff[*size - 1] = '\0';
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
	char cur_env[1024];
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
/**
 * execute_cmd - executes a command
 * @path: path to command
 * @args: arguments to command
 * @envp: environment variables
 * Return: 0 if successful, otherwise -1
 */
int execute_cmd(char *path, char **args, char **envp)
{
	execve(path, args, envp);

	exit(2);
}
/**
 * find_path - finds the path to a command
 * @path: path to search
 * @input: command to search for in path variable (e.g. ls)
 * Return: pointer to path if found, otherwise NULL
 */
char *find_path(char *path_i, char *input)
{
	char *path;
	char *chank = NULL;

	if (path_i)
	{
		path = _strdup(path_i);
		chank = _strtok(path, ":");
	}
	else
	{
		return (NULL);
	}
	while (chank != NULL && *path_i)
	{
		size_t buffer_size = _strlen(chank) + 1 + _strlen(input) + 1;
		char *buffer = malloc(buffer_size);

		int i = 0;
		int j = 0;
		int x = 0;

		while (chank[j])
		{
			buffer[i] = chank[j];
			i++;
			j++;
		}

		buffer[i] = '/';
		i++;

		while (input[x])
		{
			buffer[i] = input[x];
			i++;
			x++;
		}

		buffer[i] = '\0';

		if (access(buffer, X_OK) == 0)
		{
			free(path);
			return buffer;
		}

		free(buffer);

		chank = _strtok(NULL, ":");
	}
	free(path);
	return NULL;
}
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
void getc_command(char *str, char *c_command)
{
	int i = 0, j = 0;

	while (str[i] == 2 || str[i] == ' ')
	{
		i++;
	}
	if (i < BUFSIZ)
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
	char *path = get_path(envp);
	int status = 0;

	argv[argc - 1] = argv[argc - 1];
	while (1)
	{
		char str[BUFSIZ];
		char c_command[BUFSIZ];
		int str_Size;

		get_input(str, &str_Size);
		getc_command(str, c_command);
		while (*c_command)
		{
			status = handle_command(c_command, path, envp, status);
			getc_command(str, c_command);
		}
		if (!_strcmp(str, "exit") || str_Size == 0)
		{
			break;
		}
	}
	if (status)
		exit(status);
	else
		return (status);
}
