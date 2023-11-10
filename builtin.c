#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
    int exitcheck;

    if (info->argv[1])  /* If there is an exit argument */
    {
        exitcheck = _erratoi(info->argv[1]);
        if (exitcheck == -1)
        {
            info->status = 2;
            perror("Illegal number: ");
            write(STDERR_FILENO, info->argv[1], _strlen(info->argv[1]));
            write(STDERR_FILENO, "\n", 1);
            return (1);
        }
        info->err_num = _erratoi(info->argv[1]);
        return (-2);
    }
    info->err_num = -1;
    return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
        perror("TODO: >>getcwd failure emsg here<<\n");
    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
        else
            chdir_ret = chdir(dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            write(STDOUT_FILENO, s, _strlen(s));
            write(STDOUT_FILENO, "\n", 1);
            return (1);
        }
        write(STDOUT_FILENO, _getenv(info, "OLDPWD="), _strlen(_getenv(info, "OLDPWD=")));
        write(STDOUT_FILENO, "\n", 1);
        chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
    }
    else
        chdir_ret = chdir(info->argv[1]);
    if (chdir_ret == -1)
    {
        perror("can't cd to ");
        write(STDERR_FILENO, info->argv[1], _strlen(info->argv[1]));
        write(STDERR_FILENO, "\n", 1);
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
    char **arg_array;

    arg_array = info->argv;
    write(STDOUT_FILENO, "help call works. Function not yet implemented \n", 47);
    if (0)
        write(STDOUT_FILENO, *arg_array, _strlen(*arg_array)); /* temp att_unused workaround */
    return (0);
}

