#include "shell.h"
#define MAX_PATH_SIZE 1024
int _setenv(const char *name, const char *value, int overwrite);
char *_getenv(const char *name);
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

	char *home_dir = _getenv("HOME");

	if (_strcmp(cmd_argv[0], "cd") == 0)
	{
		if (cmd_argv[1] == NULL || _strcmp(cmd_argv[1], "~") == 0)
		{
			if (home_dir != NULL)
			{
				if (chdir(home_dir) == 0)
				{
					_setenv("PWD", home_dir, 1);
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

		else if (_strcmp(cmd_argv[1], "-") == 0)
		{
			char *prev_dir = _getenv("OLDPWD");

			if (prev_dir != NULL)
			{
				if (chdir(prev_dir) == 0)
				{
					_setenv("PWD", prev_dir, 1);
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
			char current_dir[MAX_PATH_SIZE];

			if (getcwd(current_dir, sizeof(current_dir)) != NULL)
			{
				if (chdir(target_dir) == 0)
				{
					_setenv("OLDPWD", current_dir, 1);
					if (getcwd(current_dir, sizeof(current_dir)) != NULL)
					{
						_setenv("PWD", current_dir, 1);
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
		write(STDERR_FILENO, "Usage: cd [DIRECTORY]\n", 31);
	}
}
/**
 * _getenv - gets env variable
 * @name: name of env var
 *
 * Return: NULL if success
 */
char *_getenv(const char *name)
{
	int i = 0, name_len;
	char *env_var, *equals_pos;

	while (environ[i])
	{
		env_var = environ[i++];
		equals_pos = my_strchr(env_var, '=');

		if (equals_pos)
		{
			name_len = equals_pos - env_var;
			if (_strncmp(env_var, name, name_len) == 0)
			{
				return (equals_pos + 1);
			}
		}
	}

	return (NULL);
}
/**
 * _setenv - set env variable
 * @name: name of var
 * @value: value of var
 * @overwrite: overwrite
 *
 * Return: 0 if success, otherwise fail
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0, name_len;
	char *env_var, *equals_pos, *new_env_var;

	while (environ[i])
	{
		env_var = environ[i++];
		equals_pos = my_strchr(env_var, '=');

		if (equals_pos)
		{
			name_len = equals_pos - env_var;
			if (_strncmp(env_var, name, name_len) == 0)
			{
				if (overwrite)
				{
					my_strncpy(equals_pos + 1, value, my_strlen(value));
				}
				return (0);
			}
		}
	}
	new_env_var = malloc(my_strlen(name) + my_strlen(value) + 2);
	if (!new_env_var)
	{
		return (-1);
	}

	_sprintf(new_env_var, "%s=%s", name, value);
	environ[i] = new_env_var;

	return (0);
}
