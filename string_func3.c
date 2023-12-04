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
	return (envp_dup);
}
/**
 * _strstr - locates a substring in a string
 * @the_big_str: pointer to string
 * @the_little_str: pointer to substring
 * Return: pointer to the beginning of the located sub
 * string, or NULL if the substring is not found.
 * Description: This function locates a substring.
 */
char *_strstr(char *the_big_str, char *the_little_str)
{
	int x = 0, y;

	while (the_big_str[x])
	{
		y = 0;

		while (the_little_str[y])
		{
			if (the_big_str[x + y] != the_little_str[y])
			{
				break;
			}

			y++;
		}

		if (!the_little_str[y])
		{
			return (the_big_str + x);
		}

		x++;
	}

	return (NULL);
}
