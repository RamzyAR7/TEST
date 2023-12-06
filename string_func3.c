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

	envp_dup = (char **)malloc(sizeof(char *) * (rows + 1));

	if (envp_dup == NULL)
	{
		free(envp_dup);
	}

	for (i = 0; envp[i]; i++)
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
	int x = 0, y = 0, z = 0;

	while (the_big_str[x] != '\0')
	{
		y = 0;
		z = x;
		while (the_little_str[y] == the_big_str[z] && the_little_str[y])
		{
			y++;
			z++;
		}
		if (the_little_str[y] == '\0')
		{
			return (the_big_str + x);
		}
		x++;
	}
	return (NULL);
}
void *_realloc(void *ptr, int new_size)
{
	void *temp;

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}
	temp = malloc(new_size);
	intail_NULL(temp, new_size);
	_memcopy(temp, ptr, new_size - 1);
	free(ptr);
	return (temp);
}
int empty_text(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ')
			return (i);
		i++;
	}
	return (0);
}

int remove_read_spaces(char *str)
{
	int strSize = _strlen(str);
	int i = 0;

	while (str[i] == ' ')
	{
		i++;
	}
	if (i)
	{
		if (i == strSize - 2)
		{
			intail_NULL(str, strSize);
			return (0);
		}
		else
		{
			_strcpy(str, str + i);
		}
	}
	i = 0;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			int j = empty_text(str + i + 1);
			printf("j=%d\n", j);
			if (j)
				_strcpy(str + i + 1, str + i + j + 1);
			else
				intail_NULL(str + i, strSize);
		}
		i++;
	}
	return (_strlen(str));
}

void _free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
