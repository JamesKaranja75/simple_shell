#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100
#define MAX_ALIASES 100
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_VALUE 100
#define BUF_FLUSH -1

typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

typedef struct
{
char *name;
char *pathstr;
char *cmd;
char *path;
list_t *env;
int some_data;
int argc;
char **argv;
int linecount_flag;
int histcount;
char **arg;
} info_t;


extern char **environ;

void shell_exit(char **exit_args);
int _myenv(info_t *info);
char *my_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);
void add_node_end(list_t **head, const char *str, int value);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void remove_comments(char *buf);
void build_history_list(info_t *info, char *buf, int histcount);
int shell_setenv(char **setenv_args);
char starts_with(const char *str, const char *prefix);
int shell_unsetenv(char **unsetenv_args);
int shell_cd(char **cd_args);
void execute_command(char *command);
void execute(char *command, struct stat *statbuf);
bool check_file_status(char *path, struct stat *statbuf);
int wait_for_child(pid_t child_pid, int *status);
void handle_error(const char *message);
void remove_newline(char *str, ssize_t length);
void execute_cmd(char *cmd, struct stat *st);
void handle_comments(char *command);
void handle_commands_separator(char *command);
void handle_logical_operators(char *command);
ssize_t custom_getline(char **ptr, size_t *length, FILE *stream);
char *dup_chars(char *pathstr, int start, int stop);
void custom_shell(void);
void custom_exit(void);

#endif
