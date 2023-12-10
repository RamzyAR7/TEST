#include "main.h"

void _free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

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

void *_realloc(void *ptr, int new_size)
{
	void *temp;

	if (new_size < _strlen(ptr))
	{
		_Free(ptr);
		return (NULL);
	}
	temp = _malloc(new_size);
	intail_NULL(temp, new_size);
	_memcopy(temp, ptr, _strlen(ptr));
	_Free(ptr);
	return (temp);
}

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
