#include "main.h"
#include <string.h>

void get_input(char *buff, int *size)
{
	*size = read(0, buff, BUFSIZ);
	if (*size == -1)
	{
		exit(2);
	}
	buff[*size - 1] = '\0';
}
char *get_path(char *envp[])
{
	char *path = "PATH=";
	char cur_env[100];
	char *paths;
	int i = 0;

	while (envp[i])
	{
		memcpy(cur_env, envp[i], strlen(path));
		if (strcmp(path, cur_env) == 0)
		{
			break;
		}
		i++;
	}
	return (envp[i] + strlen(path));
}
char check_many_commands(char *str)
{
	if (str[strlen(str) - 1] == ';')
	{
		return (';');
	}
	else if (strcmp(str, "&&") == 0)
	{
		return ('&');
	}
	else if (strcmp(str, "||") == 0)
	{
		return ('|');
	}
	return (0);
}
void add_args(char **arguments_array, char *argument)
{
	char **temp;
	int i = 0;

	if (arguments_array)
	{
		while (arguments_array[i++])
			;
	}
	else
	{
		i++;
	}
	temp = (char **)malloc(sizeof(arguments_array) * i);
	i = 0;
	printf("outloop loop\n");
	while (arguments_array && arguments_array[i])
	{
		printf("in loop");
		temp[i] = (char *)malloc(strlen(arguments_array[i]));
		strcpy(temp[i], arguments_array[i]);
		free(arguments_array[i]);
		i++;
	}
	temp[i] = (char *)malloc(strlen(argument));
	strcpy(temp[i], argument);
	free(arguments_array);
	arguments_array = temp;
}
int handle_command(char *command, char *path)
{
	char *first_sigment = strtok(command, " ");
	char **arguments = NULL;

	add_args(arguments, first_sigment);
	while (first_sigment != NULL)
	{
		char *cur_sigment = strtok(NULL, " ");

		if (cur_sigment == NULL)
		{
			break;
		}
		else
		{
			if (check_many_commands(cur_sigment))
			{
				printf("\ntest\n");
			}
			else
			{

				add_args(arguments, cur_sigment);
				printf("c:%s\n", arguments[0]);
				printf("c:%s\n", arguments[1]);
			}
		}
	}
}

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
