#include "main.h"

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * @envp: array of environment variables
 * Return: 0 if successful, otherwise 1
 */
int main(int argc, char *argv[], char *envp[])
{
	int active_mode = isatty(STDIN_FILENO);
	char *symbol = "-> ";
	int fd = STDIN_FILENO;

	_state(0);
	if (argc == 2)
		check_file_mode(argv[1], &fd, &active_mode);
	_enviornment(dup_2D(envp), 1);
	shell_core(symbol, fd, active_mode);
	_enviornment(NULL, 0);
	_alias(NULL, 0);
	return (State);
}
void check_file_mode(char *filename, int *fd, int *active_mode)
{
	if (access(filename, R_OK) != -1)
	{
		*active_mode = 0;
		*fd = open(filename, O_RDONLY);

		if (!Fsize(filename))
			exit(0);
	}
	else
	{
		print(STDERR_FILENO, "./hsh: 0: cannot open ", filename, ": No such file\n", NULL);
		exit(2);
	}
}
int Fsize(char *fname)
{
	struct stat st;

	stat(fname, &st);
	return (st.st_size);
}
void shell_core(char *symbol, int fd, int active_mode)
{
	do
	{
		char *str = _malloc(BUFFER_SIZE);
		char *c_command = _malloc(BUFFER_SIZE);
		int read_size = 0;
		int buffer_size = BUFFER_SIZE;
		int command_size = BUFFER_SIZE;

		intail_NULL(str, buffer_size);
		intail_NULL(c_command, command_size);
		if (active_mode == 1)
			print(STDOUT_FILENO, symbol, NULL);
		get_input(&str, &read_size, &buffer_size, fd);
		buffers(&str, &c_command, 1);
		getc_command(str, &c_command, &command_size);
		while (*c_command)
		{
			handle_command(c_command);
			getc_command(str, &c_command, &command_size);
		}
		if (read_size == 0)
		{
			_Free(str);
			_Free(c_command);
			break;
		}
		_Free(str);
		_Free(c_command);
	} while (active_mode);
}
