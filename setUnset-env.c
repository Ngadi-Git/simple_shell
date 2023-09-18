#include "shell.h"
/**
 * handleSetenv - handle setenv
 * @cmd_argv: pointer to a pointer
 *
 * Return: 0 on success otherwise fail
 */
int handleSetenv(char **cmd_argv)
{
	if (cmd_argv[1] != NULL && cmd_argv[2] != NULL)
	{
		if (setenv(cmd_argv[1], cmd_argv[2], 1) == -1)
		{
			perror("setenv");
			return (1);
		}
	}
	else
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
		return (1);
	}
	return (0);
}

/**
 * handleUnsetenv - handle unsetenv
 * @cmd_argv: pointer to a pointer
 *
 * Return: 0 on success otherwise fail
 */
int handleUnsetenv(char **cmd_argv)
{
	if (cmd_argv[1] != NULL)
	{
		if (unsetenv(cmd_argv[1]) == -1)
		{
			perror("unsetenv");
			return (1);
		}
	}
	else
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 28);
		return (1);
	}
	return (0);
}
