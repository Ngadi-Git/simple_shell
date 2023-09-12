#include "shell.h"

void handle_string(char *str, size_t size, size_t *n, va_list args);
void handle_int(char *str, size_t size, size_t *n, va_list args);

/**
 * my_strlen - cal the length of a the user's input
 * @str: string to be counted
 *
 * Return: the length of user's input
 */
size_t my_strlen(const char *str)
{
	const char *s;

	for (s = str; *s; ++s)
	;

	return (s - str);
}
/**
 * _strncmp - Compares two strings up to n bytes
 * @s1: First string
 * @s2: Second string
 * @n:  Size of sting
 *
 * Return: Always 0 if successfull otherwise it fails.
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && (*s1 != '\0' || *s2 != '\0'))
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}
/**
 * cus_getenv - Gets the filename from environ
 * @filename: File to search
 *
 * Return: Always 0 if successfull otherwise it fails
 */
char *cus_getenv(const char *filename)
{
	int i;
	size_t s_len;

	i = 0;
	s_len = my_strlen(filename);

	if (filename == NULL || environ[i] == NULL)
		return (NULL);

	while (environ[i] != NULL)
	{
		if (_strncmp(filename, environ[i], s_len) == 0 && environ[i][s_len] == '=')
			return (&environ[i][s_len + 1]);

		i++;

	}
	return (NULL);
}
/**
 * my_snprintf - custom snprintf function
 * @str: string
 * @size: size of string
 * @format: string format
 *
 * Return: formatted string
 */
int my_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list args;
	size_t i = 0, n = 0;

	va_start(args, format);

	while (format[i] != '\0' && n < size - 1)
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				handle_string(str, size, &n, args);
			else if (format[i] == 'd')
				handle_int(str, size, &n, args);
		}
		else
			str[n++] = format[i];
		i++;
	}
	str[n] = '\0';
	va_end(args);
	return (n);
}
/**
 * my_strncpy - custom string copy
 * @dest: destination
 * @src: source
 * @n: size/length
 *
 * Return: a copy of string if success
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';

	return (dest);
}
