#include "shell.h"
char *my_strncpy(char *dest, const char *src, size_t n);
char *cus_getenv(const char *filename);
int my_snprintf(char *str, size_t size, const char *format, ...);


/**
 * executeAbsPATH - executes the command if PATH is include
 * @cmd_argv: command
 * @name: name of programme
 *
 */
void executeAbsPATH(char **cmd_argv, char *name)
{
	pid_t child_pid;
	int status;
	int i;
	size_t arg_len;
	char *arg;

	if (access(cmd_argv[0], X_OK) == 0)
	{
		for (i = 1; cmd_argv[i] != NULL; i++)
		{
			arg = cmd_argv[i];
			arg_len = my_strlen(arg);
			if (arg[0] == '"' && arg[arg_len - 1] == '"')
			{
				arg[arg_len - 1] = '\0';
				cmd_argv[i] = arg + 1;
			}
		}
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Error:");
			exit(1);
		}
		if (child_pid == 0)
		{
			execve(cmd_argv[0], cmd_argv, environ);
			perror(name);
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}
	else
	{
		perror(name);
	}
}
/**
 * executeRelPATH - executes the command if PATH is not included
 * @cmd_argv: command
 * @name: name of programme
 */
void executeRelPATH(char **cmd_argv, char *name)
{
	char *path;
	char path_copy[MAX_INPUT_SIZE];
	int status;
	char *token;
	char full_path[MAX_INPUT_SIZE];
	pid_t child_pid;

	path = cus_getenv("PATH");
	if (path != NULL)
	{
		my_strncpy(path_copy, path, MAX_INPUT_SIZE);
		token = strtok(path_copy, ":");
		while (token != NULL)
		{
			my_snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd_argv[0]);
			if (access(full_path, X_OK) == 0)
			{
				child_pid = fork();

				if (child_pid == -1)
				{
					perror("Error:");
					exit(1);
				}
				if (child_pid == 0)
				{
					execve(full_path, cmd_argv, environ);
					perror(name);
					exit(1);
				}
				else
				{
					wait(&status);
					break;
				}
			}
			token = strtok(NULL, ":");
		}
		if (token == NULL)
			perror(name);
	}
}
