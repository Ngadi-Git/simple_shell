#include "shell.h"
size_t my_strlen(const char *str);
void executeAbsPATH(char **cmd_argv, char *name);
void executeRelPATH(char **cmd_argv, char *name);
/**
 * readInput - reads user's input
 * @input: user input (pointer)
 *
 */
void readInput(char **input)
{
	size_t input_len;
	ssize_t read_input;
	const char *prompt = "#cisfun$ ";

	input_len = 0;
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prompt, my_strlen(prompt));
		fflush(stdout);
	}
	read_input = _getline(input, &input_len, stdin);
	if (read_input == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(*input);
		exit(0);
	}
	print_env(*input);
	input_len = my_strlen(*input);
	if (input_len > 0 && (*input)[input_len - 1] == '\n')
		(*input)[input_len - 1] = '\0';
}
/**
 * parseInput - parses the entered input
 * @input: input passed
 * @cmd_argv: pointer to a pointer
 *
 */
void parseInput(char *input, char **cmd_argv)
{
	int cmd_argc = 0;
	const char *delim = " ";
	char *token = _strtok(input, delim);

	while (*input == ' ')
		input++;
	while (token != NULL && cmd_argc < MAX_ARGS - 1)
	{
		if (*token != '\0')
		{
			cmd_argv[cmd_argc++] = token;
		}
		token = _strtok(NULL, delim);
	}
	cmd_argv[cmd_argc] = NULL;
}
/**
 * executeCommand - executes the command passed
 * @cmd_argv: pointer to a pointer
 * @name: name of programme
 *
 */
void executeCommand(char **cmd_argv, char *name)
{
	int exit_status;

	if (cmd_argv[0] == NULL)
		return;
	if (_strcmp(cmd_argv[0], "exit") == 0)
	{
		if (cmd_argv[1] != NULL)
		{
			exit_status = _atoi(cmd_argv[1]);
			exit(exit_status);
		}
		else
		{
			exit(0);
		}
	}
	else if (_strcmp(cmd_argv[0], "setenv") == 0)
		handleSetenv(cmd_argv);
	else if (_strcmp(cmd_argv[0], "unsetenv") == 0)
		handleUnsetenv(cmd_argv);
	else if (cmd_argv[0][0] == '/')
		executeAbsPATH(cmd_argv, name);
	else
		executeRelPATH(cmd_argv, name);
}

/**
 * main - Entry point for shell program
 * @argc: Number of command line arguments
 * @argv: Array of command line arguments
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	char *input = NULL;
	char *cmd_argv[MAX_ARGS];
	int should_exit = 0;

	(void) argc;

	while (!should_exit)
	{
		readInput(&input);
		parseInput(input, cmd_argv);
		executeCommand(cmd_argv, argv[0]);
	}
	free(input);
	return (0);
}
