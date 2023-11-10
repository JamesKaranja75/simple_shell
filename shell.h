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
#include <errno.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 100
#define MAX_ALIASES 100
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_VALUE 100
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

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
int env_changed;
char **environ;
char *fname;
int status;
char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int err_num;
list_t *history;
list_t *alias;
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
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
extern char **list_to_strings(list_t *list);
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _erratoi(char *s);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *node_starts_with(list_t *node, char *prefix, char c);
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int bfree(void **ptr);

#endif
