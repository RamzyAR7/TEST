#include "main.h"

/**
 * env_dup - duplicates the environment
 * @envp: environment
 * Return: pointer to the duplicated environment
 */
char **env_dup(char *envp[])
{
	int i = 0;
	char **envp_dup;

	while (envp[i])
		i++;
	envp_dup = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		envp_dup[i] = _strdup(envp[i]);
		i++;
	}
	envp_dup[i] = NULL;
	return (envp_dup);
}
/**
 * handle_setenv - handles the setenv built-in
 * @envp_i: environment
 * @argv: arguments
 * Return: 0 on success, -1 on failure
*/
int handle_setenv(char *envp_i[], char *argv[])
{
	int i = 0;
	char **envp = env_dup(envp_i);

	char *chank_value;
	char *chank_key;

	while (envp[i])
	{
		chank_key = _strtok(envp[i], "=");
		chank_value = _strtok(NULL, "=");
		if (_strcmp(chank_key, argv[1]) == 0)
		{
			envp[i] = malloc(sizeof(argv[1]) + sizeof(argv[2]) + 2);
			envp[i] = _strcat(argv[1], "=");
			envp[i] = _strcat(envp[i], argv[2]);
			envp[i] = _strcat(envp[i], "\0");
			arguments_free(envp);
			return (0);
		}
		i++;
	}
	envp[i] = malloc(sizeof(argv[1]) + sizeof(argv[2]) + 3);
	envp[i] = _strcat(argv[1], "=");
	envp[i] = _strcat(envp[i], argv[2]);
	envp[i] = _strcat(envp[i], "\0");

	arguments_free(envp);
	return (0);
}
/**
 * handle_unsetenv - handles the unsetenv built-in
 * @envp: environment
 * @argv: arguments
 * Return: 0 on success, -1 on failure
*/
int handle_unsetenv(char *envp[], char *argv[])
{
	int i = 0;
	char *chank_key;

	while (envp[i] != NULL)
	{
		chank_key = _strtok(envp[i], "=");
		if (chank_key && _strcmp(chank_key, argv[1]) == 0)
		{
			free(envp[i]);

			while (envp[i] != NULL)
			{
				envp[i] = envp[i + 1];
				i++;
			}
			envp[i] = NULL;

			return (0);
		}
		i++;
	}
}
