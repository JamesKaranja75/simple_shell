#include "shell.h"

/**
 * shell_cd - Handles the cd built-in command.
 * @cd_args: The arguments for cd command.
 *
 * Return: 0 on success, -1 on failure.
 */
int shell_cd(char **cd_args)
{
char *new_directory = NULL;
char *current_directory = getcwd(NULL, 0);
if (!cd_args[1])
{
/* If no argument is provided, change to the user's home directory. */
new_directory = getenv("HOME");
}
else if (strcmp(cd_args[1], "-") == 0)
{
/* Handle "cd -" to switch to the previous working directory. */
new_directory = getenv("OLDPWD");
}
else
{
new_directory = cd_args[1];
}

if (chdir(new_directory) == -1)
{
/* Print an error message to stderr on failure. */
perror("cd");
return (-1);
}

/* Update the PWD environment variable. */
current_directory = getcwd(NULL, 0);
setenv("PWD", current_directory, 1);
free(current_directory);

/* Update the OLDPWD environment variable to the previous working directory. */
setenv("OLDPWD", new_directory, 1);

return (0);
}
