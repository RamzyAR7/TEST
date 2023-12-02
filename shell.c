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
		memcpy(cur_env, envp[i], _strlen(path));
		if (_strcmp(path, cur_env) == 0)
		{
			break;
		}
		i++;
	}
	return (envp[i] + _strlen(path));
}
char check_many_commands(char *str)
{
	if (str[_strlen(str) - 1] == ';')
	{
		return (';');
	}
	else if (_strcmp(str, "&&") == 0)
	{
		return ('&');
	}
	else if (_strcmp(str, "||") == 0)
	{
		return ('|');
	}
	return (0);
}
void add_args(char ***arguments_array, char *argument)
{
	int i = 0;
	char **temp;

	// Count the number of existing arguments
	while (*arguments_array && (*arguments_array)[i])
		i++;

	// Allocate memory for the new array of pointers
	temp = (char **)malloc((i + 2) * sizeof(char *));

	// Copy existing arguments to the new array
	for (int j = 0; j < i; j++)
	{
		temp[j] = (char *)malloc(strlen((*arguments_array)[j]) + 1);
		_strcpy(temp[j], (*arguments_array)[j]);
		free((*arguments_array)[j]);
	}
	// Allocate memory for the new argument and add it to the new array
	temp[i] = (char *)malloc(_strlen(argument) + 1);
	_strcpy(temp[i], argument);

	// Set the end of the new array to NULL
	temp[i + 1] = NULL;

	// Free the old array of pointers
	free(*arguments_array);

	// Update the pointer to point to the new array
	*arguments_array = temp;
}
int handle_command(char *command, char *path)
{
	char *first_sigment = _strtok(command, " ");
	char **arguments = NULL;

	add_args(&arguments, first_sigment);
	while (first_sigment != NULL)
	{
		char *cur_sigment = _strtok(NULL, " ");

		if (cur_sigment == NULL)
		{
			break;
		}
		else
		{
			if (check_many_commands(cur_sigment))
			{
			}
			else
			{

				add_args(&arguments, cur_sigment);
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
