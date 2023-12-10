#include "main.h"

/**
 * handle_cd - handles the cd command
 * @arguments: pointer to array of arguments
 * Return: 0 if successful, otherwise 1
 * This function is not portable. It will only work on Linux.
 * by ashraf & ramzy
 */
int handle_cd(char **arguments)
{
	char cwd[BUFFER_SIZE];
	char *cd = NULL;
	char **pwd, **oldpwd;

	getcwd(cwd, sizeof(cwd));
	pwd = creat_2D(3, "setenv", "PWD", arguments[1]);
	oldpwd = creat_2D(3, "setenv", "OLDPWD", cwd);

	if (arguments[1] && *arguments[1])
	{
		if (!handle_cd_helper(arguments, pwd, oldpwd, cd, cwd))
			return (0);
	}
	else
	{
		cd = get_env_value("HOME");
		if (cd)
		{
			_Free(pwd[2]);
			pwd[2] = cd;
			chdir(cd);
		}
	}
	handle_setenv(pwd);
	handle_setenv(oldpwd);
	arguments_free(arguments);
	return (0);
}
/**
 * handle_cd_helper - handle cd
 * @arguments: pointer to array of arguments
 * @pwd: pointer to array of pwd arguments
 * @oldpwd: pointer to array of oldpwd arguments
 * @cd: pointer of string should go to
 * @cwd: pointer of string of current directory
 * Return: 1 if successful, otherwise 0
 * by ashraf & ramzy
 */
int handle_cd_helper(char **arguments, char **pwd,
					 char **oldpwd, char *cd, char *cwd)
{
	if (_strcmp(arguments[1], "-") == 0)
	{
		cd = get_env_value("OLDPWD");
		if (cd)
		{
			_Free(pwd[2]);
			pwd[2] = cd;
			chdir(cd);
			getcwd(cwd, sizeof(cwd));
			print(STDOUT_FILENO, cwd, "\n", NULL);
		}
		else
		{
			print(STDOUT_FILENO, cwd, "\n", NULL);
			_Free(oldpwd[2]);
			_Free(pwd[2]);
		}
	}
	else
	{
		if (chdir(arguments[1]) == -1)
		{
			if (errno == ENOENT)
			{
				char *error = "./hsh: 1: cd: can't cd to ";

				print(STDERR_FILENO, error, arguments[1], "\n", NULL);
			}
			else if (errno == EACCES)
			{
				char *error = "./hsh: 1: cd: can't cd to ";

				print(STDERR_FILENO, error, arguments[1], "\n", NULL);
			}
			arguments_free(pwd), arguments_free(oldpwd), arguments_free(arguments);
			return (0);
		}
	}
	return (1);
}
