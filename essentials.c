#include "main.h"

/**
 * _free - free pointer and set it to NULL
 * @ptr: pointer to free (void **)
 * Return: void
 * by ashraf & ramzy
 */
void _free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/**
 * _malloc - allocate memory and check if it failed
 * @size: size of memory to allocate (unsigned int)
 * Return: pointer to allocated memory (void *)
 * by ashraf & ramzy
 */
void *_malloc(unsigned int size)
{
	void *str = malloc(size);

	if (!str)
	{
		_Free(str);
		print(STDOUT_FILENO, "./hsh :malloc failed\n", NULL);
		exit(-1);
	}
	intail_NULL(str, size);
	return (str);
}

/**
 * _realloc - reallocate memory and check if it failed
 * @ptr: pointer to reallocate (void **)
 * @new_size: new size of memory to allocate (unsigned int)
 * Return: pointer to reallocated memory (void *)
 * by ashraf & ramzy
 */
void *_realloc(void *ptr, int new_size)
{
	void *temp;

	if (new_size < _strlen(ptr))
	{
		_Free(ptr);
		return (NULL);
	}
	temp = _malloc(new_size);
	_memcopy(temp, ptr, _strlen(ptr));
	_Free(ptr);
	return (temp);
}

/**
 * _read - read from file descriptor and check if it failed
 * @fd: file descriptor to read from (int)
 * @str: buffer to read into (char *)
 * @str_size: size of buffer to read into (int)
 * Return: number of characters read (int)
 * by ashraf & ramzy
 */
int _read(int fd, char *str, int str_size)
{
	int read_chars = 0;

	read_chars = read(fd, str, str_size);
	if ((str)[read_chars - 1] == '\n')
		(str)[read_chars - 1] = '\0';
	if (read_chars == -1)
	{
		_Free(str);
		exit(2);
	}
	return (read_chars);
}

/**
 * print - print to file descriptor
 * @fd: file descriptor to print to (int)
 * Return: void
 * by ashraf & ramzy
 */
void print(int fd, ...)
{
	va_list args;
	char *c_arg, *str = NULL;
	int write_to = 0;

	va_start(args, fd);
	write_to = fd;
	c_arg = va_arg(args, char *);
	str = _strdup(c_arg);
	c_arg = va_arg(args, char *);
	while (c_arg)
	{
		str = _realloc(str, _strlen(str) + _strlen(c_arg) + 1);
		_strcat(str, c_arg);
		c_arg = va_arg(args, char *);
	}
	write(write_to, str, _strlen(str));
	_Free(str);
	va_end(args);
}
