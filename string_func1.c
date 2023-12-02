#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _strchr - locates a character in a string
 * @str: pointer to string
 * @c: character to locate
 * Return: pointer to first occurrence of c in str
 */
int *_strchr(const char *str, int c)
{
	while (*str != (char)c)
	{
		if (!*str)
		{
			return (NULL);
		}
		str++;
	}
	return ((int *)str);
}
/**
 * _strtok - tokenizes a string
 * @str: pointer to string
 * @delimiters: pointer to delimiters
 * Return: pointer to next token
 */
char *_strtok(char *str, const char *delimiters)
{
	static char *chank;
	char *ret;

	if (str)
		chank = str;
	else if (!*chank)
		return (NULL);

	ret = chank;

	while (*chank && !_strchr(delimiters, *chank))
		chank++;

	if (*chank)
		*chank++ = '\0';

	return (ret);
}
/**
 * _strlen - returns the length of a string
 * @p_string: pointer to string
 * Return: length of string
 */
int _strlen(char *p_string)
{
	size_t i = 0;

	while (p_string[i] != '\0')
		i++;
	return (i);
}
/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @p_string: pointer to string
 * Return: pointer to new string
 */
char *_strdup(char *p_string)
{
	if (p_string == NULL)
		return (NULL);

	size_t i = 0;
	char *str;
	int len = _strlen(p_string);

	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);

	while (p_string[i] != '\0')
	{
		str[i] = p_string[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/**
 * _strcpy - copies the string pointed to by src
 * @copy_to: pointer to destination
 * @copy_from: pointer to source
 * Return: pointer to destination
 */
char *_strcpy(char *copy_to, char *copy_from)
{
	int i = 0;

	while (copy_from[i])
	{
		copy_to[i] = copy_from[i];
		i++;
	}
	return (copy_to);
}
