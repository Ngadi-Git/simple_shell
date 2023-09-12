#include "shell.h"
/**
 * print_env - functions same way as printenv
 * @input: command input
 *
 */
void print_env(char *input)
{
	char **env;

	if (_strcmp(input, "env") == 0)
	{
		for (env = environ; *env != NULL; env++)
		{
			write(STDOUT_FILENO, *env, my_strlen(*env));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
