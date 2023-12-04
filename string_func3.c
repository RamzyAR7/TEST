#include "main.h"

/**
 * _strcpy - copies the string pointed to by src
 * @copy_to: pointer to destination
 * @copy_from: pointer to source
 * Return: pointer to destination
 */
char *_strcpy(char *copy_to, char *copy_from)
{
	int i = 0;

	while (copy_from && copy_from[i])
	{
		copy_to[i] = copy_from[i];
		i++;
	}
	copy_to[i] = '\0';
	return (copy_to);
}
/**
 * env_dup - duplicates the environment
 * @envp: pointer to environment
 * Return: pointer to duplicated environment
 * Description: This function duplicates the environment
 * and returns a pointer to the duplicated environment.
 */
char **env_dup(char *envp[])
{
	int rows = 0, i = 0;
	char **envp_dup;

	while (*(envp + rows) != NULL)
	{
		rows++;
	}

	envp_dup = (char **)malloc(sizeof(char *) * rows + 1);

	if (envp_dup == NULL)
	{
		free(envp_dup);
	}

	for (i = 0; i < rows; i++)
	{
		envp_dup[i] = _strdup(envp[i]);
	}
	envp_dup[i] = NULL;
	return (env_dup);
}
