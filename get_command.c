#include "main.h"

/**
 * getc_command - get command from user input (char *)
 * @str: user input (char *)
 * @c_command: pointer to command to be returned (char **)
 * @cmd_size: pointer to size of command to be returned (int *)
 * Return: void
 * by ashraf & ramzy
 */
void getc_command(char *str, char **c_command, int *cmd_size)
{
	int i = 0, j = 0;

	while (str[i] == 2 || str[i] == ' ')
	{
		i++;
	}
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (str[i + 1] != '\n')
			{
				str[i] = 2;
				break;
			}
			else
			{
				str[i] = 2;
				i++;
			}
		}
		else if (str[i] == ' ' && !last_space(str + i))
			break;

		else if (str[i] == ' ' && str[i + 1] == ' ')
		{
			i++;
			continue;
		}
		else
			getc_command_helper(str, c_command, cmd_size, &i, &j);
	}
	(*c_command)[j] = '\0';
	alias_replace(c_command, cmd_size);
	edit_command(c_command, cmd_size);
}
/**
 * last_space - check if last char in string is space
 * @str: string to check (char *)
 * Return: (1) if last char in string is space, (0) others (int)
 * by ashraf & ramzy
 */
int last_space(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i++] != ' ')
			return (1);
	}
	return (0);
}
/**
 * getc_command_helper - helper function for getc_command
 * @str: user input (char *)
 * @c_command: pointer to command to be returned (char **)
 * @cmd_size: pointer to size of command to be returned (int *)
 * @i: pointer to index of user input (int *)
 * @j: pointer to index of command to be returned (int *)
 * Return: void
 * by ashraf & ramzy
 */
void getc_command_helper(char *str, char **c_command,
						 int *cmd_size, int *i, int *j)
{
	if (*j < *cmd_size - 2)
	{
		(*c_command)[*j] = str[*i];
		str[*i] = 2;
		*i += 1;
		*j += 1;
	}
	else
	{
		*c_command = _realloc(*c_command, *cmd_size * 2);
		*cmd_size *= 2;
		buffers(NULL, c_command, 1);
	}
}
/**
 * edit_command - edit command to replace $$, $?, and $<env>
 * @str_ptr: pointer to command to be edited (char **)
 * @str_size: pointer to size of command to be edited (int *)
 * Return: void
 * by ashraf & ramzy
 */
void edit_command(char **str_ptr, int *str_size)
{
	int i = 0;
	int temp_size = *str_size;
	char *temp = malloc(temp_size);
	char *str = *str_ptr;

	for (i = 0; str[i]; i++)
	{
		if (_strcmp(str + i, "$$") == 0)
		{
			char pid[255];

			nts(getpid(), pid);

			str = replaceTxtInd(str_ptr, pid, i, i + 1);
			i += _strlen(pid) - 1;
		}
		else if (_strcmp(str + i, "$?") == 0)
		{
			char last_exit_code[255];

			nts(State, last_exit_code);

			str = replaceTxtInd(str_ptr, last_exit_code, i, i + 1);
			i += _strlen(last_exit_code) - 1;
		}
		else if (str[i] == '$' && str[i + 1] != '$' &&
				 str[i + 1] != ' ' && str[i + 1])
		{
			edit_command_helper(str_ptr, &str, temp, &i);
		}
		else if (str[i] == '#')
		{
			if ((i && str[i - 1] == ' ') || !i)
				str[i] = '\0';
			break;
		}
	}
	_Free(temp);
}
/**
 * edit_command_helper - helper function for edit_command to replace $<env>
 * @str_ptr: pointer to command to be edited (char **) (copy of str)
 * @str: pointer to command to be edited (char *) (copy of str_ptr)
 * @temp: pointer to temp string (char *) to be used in editing
 * @index: pointer to index of command to be edited (int *) (copy of i)
 * Return: void (edited command is returned through str_ptr)
 * by ashraf & ramzy
 */
void edit_command_helper(char **str_ptr,
						 char **str, char *temp, int *index)
{
	char *value;
	int j = 0, i = *index;

	while ((*str)[i + j] && (*str)[i + j] != ' ')
		j++;
	_memcopy(temp, (*str) + i + 1, j - 1);
	temp[j - 1] = '\0';
	value = get_env_value(temp);
	if (value)
	{
		*str = replaceTxtInd(str_ptr, value, i, i + j - 1);
		*index += _strlen(value) - 1;
		_Free(value);
	}
	else
	{
		*str = replaceTxtInd(str_ptr, " ", i, i + j - 1);
	}
}
