#include "main.h"

int print_All_Alias(void)
{
	int i = 0;
	char **alias_lisr = Alias_list;

	if (alias_lisr)
		while (alias_lisr[i])
		{
			char *str = _strdup(alias_lisr[i]);
			char *ptr = _strstr(str, "=");
			*ptr = '\0';
			print(STDOUT_FILENO, str, "='", ptr + 1, "'\n", NULL);
			_Free(str);
			i++;
		}
	return (0);
}
