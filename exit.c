#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

/**
 * runShell - Run the simple shell program
 *
 * Description: Encapsulates the functionality of a basic shell program.
 * Displays a prompt, reads user input, processes "exit" command, and handles
 * unknown commands.
 */
void runShell(void)
{
char input[MAX_INPUT_SIZE];
char *command;
while (1)
{
write(STDOUT_FILENO, "MyShell> ", 9);
if (fgets(input, sizeof(input), stdin) == NULL)
{
write(STDOUT_FILENO, "\n", 1);
break;
}
input[strcspn(input, "\n")] = '\0';
command = strtok(input, " ");
if (command == NULL)
{
continue;
}
if (strcmp(command, "exit") == 0)
{
char *arg = strtok(NULL, " ");
if (arg != NULL)
{
int status_code = atoi(arg);
exit(status_code);
}
else
{
exit(0);
}
}
else
{
char unknown_msg[1024];
snprintf(unknown_msg, sizeof(unknown_msg), "Unknown command: %s\n", command);
write(STDOUT_FILENO, unknown_msg, strlen(unknown_msg));
}
}
}
