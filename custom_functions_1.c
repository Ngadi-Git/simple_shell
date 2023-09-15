#include "shell.h"

/**
 * handle_string - handles string specifier
 * @str: string
 * @size: size of string
 * @n: string
 * @args: va list
 */
void handle_string(char *str, size_t size, size_t *n, va_list args)
{
	char *s;
	size_t j = 0;

	s = va_arg(args, char *);

	while (s[j] != '\0' && *n < size - 1)
		str[(*n)++] = s[j++];
}

/**
 * handle_int - handle integer specifier
 * @str: string
 * @size: size
 * @n: string
 * @args: va list
 */
void handle_int(char *str, size_t size, size_t *n, va_list args)
{
	int d;
	int k = 0;
	char buf[32];

	d = va_arg(args, int);
	if (d == 0)
		buf[k++] = '0';
	else
	{
		if (d < 0)
		{
			buf[k++] = '-';
			d = -d;
		}
		while (d > 0)
		{
			buf[k++] = '0' + d % 10;
			d /= 10;
		}
	}
	while (--k >= 0 && *n < size - 1)
		str[(*n)++] = buf[k];
}

/**
 * c_strtok - Breaks a string into tokens.
 * @str: String to tokenize.
 * @delimeter: Delimiter characters.
 *
 * Return: Pointer to the next token, or NULL if no more tokens
 */
char *_strtok(char *str, const char *delimeter)
{
	static char *last_token;
	char *token_start;
	int in_quotes;

	in_quotes = 0;

	if (str != NULL)
		last_token = str;
	else if (last_token == NULL)
		return (NULL);

	token_start = last_token;

	while (*last_token != '\0')
	{
		if (*last_token == '"')
			in_quotes = !in_quotes;
		else if (*last_token == *delimeter && !in_quotes)
		{
			*last_token = '\0';
			last_token++;
			return (token_start);
		}
		last_token++;
	}

	if (*token_start == '\0')
	{
		last_token = NULL;
		return (NULL);
	}

	return (token_start);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: integer greater than zero if success
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

/**
 * _atoi - converts string
 * @str: string(pointer)
 *
 * Return: converted string(integer value)
 */
int _atoi(const char *str)
{
	int sign;
	long result;

	sign = 1;
	result = 0;

	while (*str == ' ' || *str == '\t' ||
				*str == '\n' ||
				*str == '\v' ||
				*str == '\f' ||
				*str == '\r')
	{
		str++;
	}

	if (*str == '-' || *str == '+')
	{
		sign = (*str == '-') ? -1 : 1;
		str++;
	}

	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
		{
			return ((sign == 1) ? INT_MAX : INT_MIN);
		}
	str++;
	}

	return (sign * result);
	}
