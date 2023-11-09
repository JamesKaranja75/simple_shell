#include "shell.h"

/**
 * exe_cmd - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int exe_cmd(info_t *info, char *path)
{
struct stat st;

(void)info;
if (!path || access(path, X_OK) != 0) /* check for execute permission */
return (0);

if (stat(path, &st) == 0) /* Use stat to get file information */
{
if (S_ISREG(st.st_mode)) /* Check if it's a regular file */
{
return (1);
}
}
return (0);
}

/**
 * dup_chars - Duplicates characters.
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
int i = 0, k = 0;
char *buf = (char *)malloc(1024); /* Use malloc to allocate memory */
if (!buf)
{
perror("malloc");
return (NULL);
}

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
 * find_path - Finds this cmd in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd if found or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (exe_cmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!path || path[0] == '\0')
{
free(path);
return (NULL);
}
strcat(path, "/");
strcat(path, cmd);
if (exe_cmd(info, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
