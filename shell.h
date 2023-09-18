#ifndef SHELL_H
#define SHELL_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <limits.h>
#define MAX_INPUT_SIZE 4096
#define MAX_ARGS 32

extern char **environ;
void executeAbsPATH(char **cmd_argv, char *name);
void executeRelPATH(char **cmd_argv, char *name);
size_t my_strlen(const char *str);
void readInput(char **input);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void print_env(char *input);
void parseInput(char *input, char **cmd_argv);
void executeCommand(char **cmd_argv, char *cmd);
char *_strcat(char *dest, const char *src);
int _atoi(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strcmp(const char *s1, const char *s2);
char *cus_getenv(const char *filename);
int my_snprintf(char *str, size_t size, const char *format, ...);
char *my_strncpy(char *dest, const char *src, size_t n);
void handle_string(char *str, size_t size, size_t *n, va_list args);
void handle_int(char *str, size_t size, size_t *n, va_list args);
char *_strtok(char *str, const char *delimeter);
int handleUnsetenv(char **cmd_argv);
int handleSetenv(char **cmd_argv);
#endif
