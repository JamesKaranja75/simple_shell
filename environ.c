#include "shell.h"

/**
 * myenv - Prints the current environment.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int myenv(info_t *info)
{
char **env = environ;

while (*env)
{
write(STDOUT_FILENO, *env, strlen(*env));
write(STDOUT_FILENO, "\n", 1);
env++;
}
(void)info; /* Unused parameter. */
return (0);
}

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
int i;

if (info->argc < 2)
{
write(STDOUT_FILENO, "Too few arguments.\n", 18);
return (1);
}
for (i = 1; i < info->argc; i++)
{
if (putenv(info->argv[i]) != 0)
{
return (1);
}
}
return (0);
}

/**
 * populate_env_list - Populates the env linked list.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
char **env = environ;
list_t *node = NULL;

while (*env)
{
list_t *new_node = malloc(sizeof(list_t));
if (new_node == NULL)
{
/* Handle memory allocation failure */
return (1);
}
new_node->str = strdup(*env);
if (new_node->str == NULL)
{
/* Handle memory allocation failure */
free(new_node);
return (1);
}
new_node->next = NULL;
if (node == NULL)
{
node = new_node;
}
else
{
list_t *temp = node;
while (temp->next)
{
temp = temp->next;
}
temp->next = new_node;
}
env++;
}
info->env = node;
return (0);
}
