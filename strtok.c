#include "shell.h"

/**
 * processInput - Reads user input, tokenizes it, and prints the tokens
 *
 * This function reads input from the user
 * tokenizes it, and prints each token.
 * It continues this process in an infinite loop until the user exits.
 */
void processInput(void)
{
char input[MAX_TOKENS][MAX_TOKEN_LENGTH]; /* 2D array for tokens */
char input_line[MAX_TOKEN_LENGTH];
int token_count = 0;
int i;
ssize_t bytes;
char *token;

while (1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "$ ", 2);
bytes = read(STDIN_FILENO, input_line, MAX_TOKEN_LENGTH);
if (bytes == -1)
{
perror("Error (read)");
exit(EXIT_FAILURE);
}
else if (bytes == 0)
{
exit(EXIT_SUCCESS);
}
input_line[bytes - 1] = '\0'; /* Remove the newline character */
token = strtok(input_line, " ");
token_count = 0;
while (token != NULL && token_count < MAX_TOKENS)
{
strncpy(input[token_count], token, MAX_TOKEN_LENGTH);
token = strtok(NULL, " ");
token_count++;
}
/* You can now use the tokenized input as needed, for example, printing them */
for (i = 0; i < token_count; i++)
{
write(STDOUT_FILENO, input[i], strlen(input[i]));
write(STDOUT_FILENO, "\n", 1);
}
}
}
