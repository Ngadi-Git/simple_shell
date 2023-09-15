#include "shell.h"
/**
 * read_char - reads chars
 * @stream: file stream to be read from
 * @buffer: buffer
 * @start: points to the next position
 * @end: points to the end position
 *
 * Return: read chars
 */
static int read_char(FILE *stream, char *buffer, size_t *start, size_t *end)
{
	ssize_t n_read;

	if (*start == *end)
	{
		n_read = read(fileno(stream), buffer, MAX_INPUT_SIZE);
		if (n_read <= 0)
		{
			return (EOF);
		}
		*start = 0;
		*end = n_read;
	}
	return (buffer[(*start)++]);
}
/**
 * initialize_line - initialize or reallocate the lineptr buffer
 * @lineptr: pointer to a pointer
 * @n: size of buffer
 *
 * Return: 0 if success otherwise fail
 */
static int initialize_line(char **lineptr, size_t *n)
{
	if (!lineptr || !n)
	{
		return (-1);
	}

	if (!*lineptr)
	{
		*n = MAX_INPUT_SIZE;
		*lineptr = malloc(*n);
		if (!*lineptr)
		{
			return (-1);
		}
	}

	return (0);
}
/**
 * _getline - custom getline function
 * @lineptr: line pointer(pointer to pointer
 * @n: size of buffer
 * @stream: file stream to be read from
 *
 * Return: number of char read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[MAX_INPUT_SIZE];
	static size_t start, end;
	size_t i;
	char C;

	if (initialize_line(lineptr, n) == -1)
	{
		return (-1);
	}
	i = 0;
	while (1)
	{
		C = read_char(stream, buffer, &start, &end);
		if (C == EOF)
			break;
		(*lineptr)[i++] = C;
		if (i == *n - 1)
		{
			if (C == '\n')
			{
				(*lineptr)[i] = '\0';
				return (i);
			}
			else
			{
				while (C != '\n' && C != EOF)
					C = read_char(stream, buffer, &start, &end);
				return (-1);
			}
		}
		if (C == '\n')
			break;
	}
	if (i == 0)
		return (-1);
	(*lineptr)[i] = '\0';
		return (i);
}
