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
	char cur_env[100];
	char *paths;
	int i = 0;

	while (envp[i])
	{
		memcpy(cur_env, envp[i], _strlen(path));
		if (_strcmp(path, cur_env) == 0)
		{
			break;
		}
		i++;
	}
	return (envp[i] + _strlen(path));
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

	return (-1);
}
/**
 * find_path - finds the path to a command
 * @path: path to search
 * @input: command to search for in path variable (e.g. ls)
 * Return: pointer to path if found, otherwise NULL
 */
char *find_path(char *path, char *input)
{
	int i = 0;
	int j = 0;
	int x = 0;

	char buffer[100];
	char *chank = _strtok(path, ":");

	while (path)
	{
		while (chank[j])
		{
			buffer[i] = chank[j];
			i++;
			j++;
		}
		buffer[i] = "/";
		i++;
		while (input[x])
		{
			buffer[i] = input[x];
			i++;
			x++;
		}
		buffer[i] = "\0";

		if (access(buffer, X_OK) == 0)
		{
			return (buffer);
		}

		chank = _strtok(NULL, ":");
	}

	return (NULL);
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

	printf("%s\n", path);
	while (1)
	{
		char str[BUFSIZ];
		int str_Size;

		get_input(str, &str_Size);
		handle_command(str, path, envp);
		if (!strcmp(str, "exit") || str_Size == 0)
		{
			printf("bye!\n");
			break;
		}
		printf("%s\n", str);
	}

	return (0);
}
