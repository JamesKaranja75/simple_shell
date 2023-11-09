#include "shell.h"

/**
 * handle_comments - Function to remove comments
 * @command: The command to process
 */
void handle_comments(char *command)
{
char *comment = strchr(command, '#');
if (comment != NULL)
{
*comment = '\0';
}
}

/**
 * handle_commands_separator - Function to handle commands separator
 * @command: The command to process
 */
void handle_commands_separator(char *command)
{
char *separator = strchr(command, ';');
while (separator != NULL)
{
*separator = '\0';
separator = strchr(separator + 1, ';');
}
}

/**
 * handle_logical_operators - Function to handle shell logical operators
 * @command: The command to process
 */
void handle_logical_operators(char *command)
{
/* Handle '&&'*/
char *and_operator = strstr(command, "&&");
char *or_operator = strstr(command, "||");

if (and_operator != NULL)
{
*and_operator = '\0';
/* Implement logic to execute the second command if the first succeeds */
}

if (or_operator != NULL)
{
*or_operator = '\0';
}
}
