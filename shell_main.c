#include "shell.h"

/**
 * main - Entry point of the program
 * @argc: arg count
 * @argw: arg vector
 * @envy: the inviron variable.
 * Return: Always 0 on success.
 */
int main(__attribute__((unused)) int argc, char *argw[], char *envy[])
{
        signal(SIGINT, SIG_IGN);
        if (isatty(STDIN_FILENO) == 1)
        {
                interactive(argw, envy);
        }
        else
                batch(argw, envy);
        return (0);
}

/**
 * interactive - execute command on the mode interactive.
 * @argw: argument vector
 * @envy: environ variable.
 */
void interactive(char *argw[], char *envy[])
{
        char *rline, **argss, *cmd_full_path;
        int cmdcounter = 1;
        struct stat statbxf;

        while (1)
        {
                write(STDOUT_FILENO, "#Home$ ", 7);
                fflush(stdout);
                rline = read_line(), argss = parse_line(rline, DLMT);
                if (!argss[0])
                {
                        free(rline), free_arr(argss);
                        continue;
                }
                else if (!is_built_in(argss, rline))
                {
                        cmd_full_path = search_full_path(argss[0]);
                        if (cmd_full_path || (stat(argss[0], &statbxf) == 0))
                        {
                                if (cmd_full_path)
                                {
                                        argss[0] = _strdup_(cmd_full_path);
                                        free(cmd_full_path);
                                }
                                creates_process(argss, envy);
                        }
                        else
                                handle_exe_err(argw, argss, cmdcounter);
                        free(rline), free_arr(argss), cmdcounter++;
                }
                else
                {
                        free(rline), free_arr(argss);
                }
        }
}

/**
 * batch - execute command on the mode non-interactive.
 * @argw: argument vector
 * @envy: environ variable.
 */

void batch(char *argw[], char *envy[])
{
        char *rline, **argss, *cmd_full_path;
        int cmdcounter = 1;
        struct stat statbxf;

        rline = read_line();
        argss = parse_line(rline, DLMT);
        if (!argss[0])
        {
                free(rline);
                free_arr(argss);
        }
        else if (!is_built_in(argss, rline))
        {
                cmd_full_path = search_full_path(argss[0]);
                if (cmd_full_path || (stat(argss[0], &statbxf) == 0) ||
                                (access(argss[0], X_OK) == 0))
                {
                        if (cmd_full_path)
                        {
                                free(argss[0]);
                                argss[0] = _strdup_(cmd_full_path);
                                free(cmd_full_path);
                        }
                creates_process(argss, envy);
                }
                else
                        handle_exe_err(argw, argss, cmdcounter);
                free(rline);
                free_arr(argss);
                cmdcounter++;
        }
        else
        {
                free(rline);
                free_arr(argss);
        }
}
