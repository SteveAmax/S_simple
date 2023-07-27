#include "shell.h"
/**
 * check_built_ins - Finds the right function needed for execution.
 * @rts: The name of the function that is needed also args[0].
 * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*check_built_ins(char *rts))(char **, char *)
{
        int j;

        built_in_t buildin[] = {
                {"unsetenv", our_unsetenv},
                {"setenv", our_setenv},
                {"exit", our_exit},
                {"env", our_env},
                {"cod", our_cod},
                {NULL, NULL}
        };

        for (j = 0; buildin[j].built != NULL; j++)
        {
                if (_strcmp_(rts, buildin[j].built) == 0)
                {
                        return (buildin[j].func);
                }
        }
        return (NULL);
}

/**
 * is_built_in - Checks for built in functions.
 * @argss: the command and its flags
 * @eline: A string represents the input from the user.
 * Return: If function is found 0. Otherwise -1.
 */
int is_built_in(char **argss, char *eline)
{
        if (check_built_ins(argss[0]) == NULL)
                return (0);
        check_built_ins(argss[0])(argss, eline);
        return (1);
}
