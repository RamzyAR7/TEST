include "main.h"

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
