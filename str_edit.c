#include "main.h"

void intail_NULL(char *str, int size)
{
	int i;

	for (i = 0; i < size; i++)
		str[i] = '\0';
}
int empty_text(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ')
			return (i);
		i++;
	}
	return (0);
}
char *replaceTxtInd(char **str1, char *str2, int startIndex, int endIndex)
{
	int len1, len2, replaceLen, newLen;
	char *result;

	if (str1 == NULL || *str1 == NULL || str2 == NULL || startIndex < 0 || endIndex < startIndex)
	{
		fprintf(stderr, "Invalid input parameters\n");
		return (NULL);
	}

	len1 = _strlen(*str1);
	len2 = _strlen(str2);
	if (startIndex >= len1 || endIndex >= len1)
	{
		fprintf(stderr, "Invalid indices\n");
		return (NULL);
	}

	replaceLen = endIndex - startIndex + 1;

	newLen = len1 - replaceLen + len2;

	result = (char *)malloc((newLen + 1) * sizeof(char));

	if (result == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (NULL);
	}

	_memcopy(result, *str1, startIndex);
	result[startIndex] = '\0';

	_strcat(result, str2);

	_strcat(result, *str1 + endIndex + 1);

	_Free(*str1);

	*str1 = result;
	return (result);
}
