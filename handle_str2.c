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

/**
 * _strcmp - compares two strings
 * @string1: first string
 * @string2: second string
 * Return: 0 if strings are equal, otherwise the difference between the first
 */
int _strcmp(char *string1, char *string2)
{
	int i = 0;

	while (string1[i] != '\0' && string2[i] != '\0')
	{
		if (string1[i] != string2[i])
		{
			return (string1[i] - string2[i]);
		}
		i++;
	}
	return (string1[i] - string2[i]);
}
/**
 * _strcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 * Return: pointer to the resulting string
 */
char *_strcat(char *s1, char *s2)
{
	int i, j;

	for (i = 0; s1[i]; i++)
		;
	for (j = 0; s2[j]; j++, i++)
		s1[i] = s2[j];
	s1[i] = '\0';
	return (s1);
}

/**
 * _memcopy - copies a block of memory
 * @copy_to: pointer to the destination memory
 * @copy_from: pointer to the source memory
 * @n: number of bytes to copy
 * Return: pointer to the destination memory
 */
void *_memcopy(char *copy_to, const char *copy_from, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		copy_to[i] = copy_from[i];
	}
	return (copy_to);
}
