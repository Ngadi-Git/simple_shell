#include "shell.h"

/**
 * _strcat - custom strcat
 * @dest: destination
 * @src: source
 *
 * Return: destination
 */
char *_strcat(char *dest, const char *src)
{
	size_t i, j;

	for (i = 0; dest[i] != '\0'; i++)
	;
	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}

/**
 * change_dir - It handles home directory navigation
 * @cmd_argv: the command line argument (~) to be handled
 *
 */
void change_dir(char **cmd_argv)
{

	char *home_dir = getenv("HOME");

	if (_strcmp(cmd_argv[0], "cd") == 0) 
	{
		if (cmd_argv[1] == NULL || _strcmp(cmd_argv[1], "~") == 0)
		{
			if (home_dir != NULL)
			{
				if (chdir(home_dir) == 0)
				{
					setenv("PWD", home_dir, 1);
				}
				else
				{
					perror("cd");
				}
			}
			else
			{
				write(STDERR_FILENO, "HOME environment variable not set.\n", 30);
			}
		}

		else if (strcmp(cmd_argv[1], "-") == 0)
		{
			char *prev_dir = getenv("OLDPWD");

			if (prev_dir != NULL)
			{
				if (chdir(prev_dir) == 0) {
					write(STDOUT_FILENO, prev_dir, 30);
					setenv("PWD", prev_dir, 1);
				}
				else
				{
					perror("cd");
				}
			}
			else
			{
				write(STDERR_FILENO, "OLDPWD environment variable not set.\n", 30);
			}
		}
		else
		{
			char *target_dir = cmd_argv[1];
			char current_dir[1024];

			if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
				if (chdir(target_dir) == 0) {
					setenv("OLDPWD", current_dir, 1);
					if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
						setenv("PWD", current_dir, 1);
					}
					else
					{
						perror("getcwd");
					}
				}
				else
				{
					perror("cd");
				}
			}
			else
			{
				perror("getcwd");
			}
		}
	}
	else
	{
		fprintf(stderr, "Usage: %s [DIRECTORY]\n", cmd_argv[0]);
	}
}
