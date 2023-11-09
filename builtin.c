#include "shell.h"

/**
 * shell_setenv - Handles the setenv built-in command.
 * @setenv_args: The arguments for setenv command.
 *
 * Return: 0 on success, -1 on failure.
 */
int shell_setenv(char **setenv_args)
{
if (setenv_args && setenv_args[1] && setenv_args[2])
{
if (setenv(setenv_args[1], setenv_args[2], 1) != 0)
{
/* Print an error message to stderr on failure.*/
write(STDERR_FILENO, "Failed to set environment variable\n", 34);
return (-1);
}
return (0);
}
else
{
/* Print an error message to stderr on incorrect syntax */
write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
return (-1);
}
}

/**
 * shell_unsetenv - Handles the unsetenv built-in command.
 * @unsetenv_args: The arguments for unsetenv command.
 *
 * Return: 0 on success, -1 on failure.
 */
int shell_unsetenv(char **unsetenv_args)
{
if (unsetenv_args && unsetenv_args[1])
{
if (unsetenv(unsetenv_args[1]) != 0)
{
/* Print an error message to stderr if the variable doesn't exist*/
write(STDERR_FILENO, "Environment variable does not exist\n", 38);
return (-1);
}
return (0);
}
else
{
/*  Print an error message to stderr on incorrect syntax.*/
write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 26);
return (-1);
}
}
