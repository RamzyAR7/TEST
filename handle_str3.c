#include "main.h"

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

	while (string && string[i])
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
 * nts - converts a number to a string
 * @num: number to convert
 * @result: buffer to store result
 * Return: void
 * by ashraf & ramzy
 */
void nts(int num, char result[])
{
	int index = 0;

	nts_recursive_helper(num, result, &index);

	result[index] = '\0';
}

/**
 * nts_recursive_helper - converts a number to a string
 * @num: number to convert
 * @result: buffer to store result
 * @index: index of buffer
 * Return: void
 * by ashraf & ramzy
 */
void nts_recursive_helper(int num, char result[], int *index)
{
	if (num < 0)
	{
		result[(*index)++] = '-';
		num = -num;
	}

	if (num / 10 != 0)
	{
		nts_recursive_helper(num / 10, result, index);
	}

	result[(*index)++] = num % 10 + '0';
}
