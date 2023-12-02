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
		handle_command(str, path);
		if (!strcmp(str, "exit") || str_Size == 0)
		{
			printf("bye!\n");
			break;
		}
		printf("%s\n", str);
	}

	return (0);
}
