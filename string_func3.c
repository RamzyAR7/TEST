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
		_Free(envp_dup);
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
		_Free(ptr);
		return (NULL);
	}
	temp = malloc(new_size);
	intail_NULL(temp, new_size);
	_memcopy(temp, ptr, new_size - 1);
	_Free(ptr);
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
			char *ptr = str + i;

			_strcpy(str, ptr);
		}
	}
	i = 0;

	while (str[i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			int j = empty_text(str + i + 1);

			if (j)
			{
				char *ptr = str + i + 1;
				char *ptr2 = str + i + j + 1;

				_strcpy(ptr, ptr2);
			}
			else
			{
				char *ptr = str + i;

				strSize = _strlen(str);
				intail_NULL(ptr, strSize);
			}
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

char *replaceTxtInd(char **str1, char *str2, int startIndex, int endIndex)
{
	int len1, len2, replaceLen, newLen;
	char *result;

	if (str1 == NULL || *str1 == NULL || str2 == NULL || startIndex < 0 || endIndex < startIndex)
	{
		fprintf(stderr, "Invalid input parameters\n");
		return (NULL);
	}

	len1 = strlen(*str1);
	len2 = strlen(str2);
	if (startIndex >= len1 || endIndex >= len1)
	{
		fprintf(stderr, "Invalid indices\n");
		return (NULL);
	}

	replaceLen = endIndex - startIndex + 1;

	newLen = len1 - replaceLen + len2;

	result = (char *)malloc((newLen + 1) * sizeof(char));

	if (result == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}

	_memcopy(result, *str1, startIndex);
	result[startIndex] = '\0';

	_strcat(result, str2);

	_strcat(result, *str1 + endIndex + 1);

	_Free(*str1);

	*str1 = result;
	return (result);
}
