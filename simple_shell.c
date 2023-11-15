#include "shell.h"

/**
 * execute_command - Execute a command in a child process
 * @command: The command to execute
 * This function forks a new process and attempts to execute the provided
 * command in the child process using execve. It waits for the child process
 * to complete in the parent process.
 */
void execute_command(char *command)
{
pid_t pid = fork();

if (pid == -1)
{
perror("fork");
_exit(EXIT_FAILURE);
}

if (pid == 0)
{
char *argv[2];
argv[0] = command;
argv[1] = NULL;
if (execve(command, argv, NULL) == -1)
{
perror("execve");
_exit(EXIT_FAILURE);
}
}
else
{
int status;
waitpid(pid, &status, 0);
}
}

/**
 * main - Entry point for the command-line interpreter
 * This function continuously prompts the user for commands, reads the input
 * and executes the user's command in a child process. It uses the write
 * system call to display the command prompt and implements a simple
 * command-line interpreter loop
 *
 * Return: Always 0 (success)
 */
int main(void)
{
char *command = NULL;
size_t len = 0;

while (1)
{
char prompt[] = "#cisfun$ ";
write(STDOUT_FILENO, prompt, sizeof(prompt) - 1); /* Exclude null terminator */

if (getline(&command, &len, stdin) == -1)
{
free(command);
write(STDOUT_FILENO, "\n", 1);
exit(0);
}

command[strcspn(command, "\n")] = '\0';

if (strcmp(command, "exit") == 0)
{
free(command);
exit(0);
}

execute_command(command);
}

free(command);
exit(0);
}
