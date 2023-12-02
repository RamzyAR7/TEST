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
int main(int argc, char *argv[], char *envp[])
{
	char *path = get_path(envp);

	printf("%s\n", path);
	while (1)
	{
		char str[BUFSIZ];
		int str_Size;

		get_input(str, &str_Size);
		if (!strcmp(str, "exit") || str_Size == 0)
		{
			printf("bye!\n");
			break;
		}
		printf("%s\n", str);
	}

	return (0);
}
