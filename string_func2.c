#include "main.h"

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
 * _atoi - converts a string to an integer
 * @string: string to convert
 * Return: integer
*/
int _atoi(char *string)
{
	int i = 0;
	int sign = 1;
	int res = 0;

	while (string[i] != '\0')
	{
		if (string[i] == '-')
		{
			sign *= -1;
		}
		else if (string[i] >= '0' && string[i] <= '9')
		{
			res = (res * 10) + (string[i] - '0');
		}
		else
		{
			break;
		}
		i++;
	}
	return (res * sign);
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
