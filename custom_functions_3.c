#include "shell.h"
/**
 * _sprintf - format string
 * @str: string
 * @format: format
 *
 */
void _sprintf(char *str, const char *format, ...)
{
	char *s, *b, buffer[32];
	int d;

	va_list args;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
			{
				s = va_arg(args, char *);
				while (*s)
				{
					*str++ = *s++;
				}
			}
			else if (*format == 'd')
			{
				d = va_arg(args, int);
				my_snprintf(buffer, sizeof(buffer), "%d", d);
				b = buffer;
				while (*b)
				{
					*str++ = *b++;
				}
			}
		}
		else
		{
			*str++ = *format;
		}
		format++;
	}
	*str = '\0';
	va_end(args);
}
/**
 * my_strchr - string
 * @s: string
 * @c: char
 *
 * Return: NULL of success
 */
char *my_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (NULL);
}
