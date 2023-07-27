#include "shell.h"
/**
 * search_full_path - search for a valid path for the command
 * @commande: the comand to look for in the path
 * Return: the full path if found , NULL otherwise.
 */

char *search_full_path(char *commande)
{
        char *full_paths;
        char **paths_token;
        int j = 0, varindex;

        varindex = find_path_index("PATH");
        if (varindex == -1)
                return (NULL);
        paths_token = parse_path(varindex, "PATH");
        if (!paths_token)
                return (NULL);

        while (paths_token[j])
        {
                full_paths = (build_full_path(paths_token[j], commande));
                if (!full_paths)
                {
                        free_arr(paths_token);
                        return (NULL);
                }
                if (access(full_paths, X_OK) == 0)
                {
                        free_arr(paths_token);
                        return (full_paths);
                }
                free(full_paths);
                j++;
        }
        free_arr(paths_token);
        return (NULL);
}

/**
 * parse_path - finds environment variable in the environ and
 * split it into tokens.
 * @index: Index of the environment variable.
 * @rts: representing the environment variable.
 * Return: on success an array of token, on fail NULL is returned.
 */
char **parse_path(int index, char *rts)
{
        char *envy_var; /*getenv("PATH");*/
        char **paths_token;
        int rlen;
        const char *dylmtr = ":";

        rlen = _strlen(rts);
        envy_var = environ[index] + (rlen + 1);
        paths_token = parse_line(envy_var, dylmtr);
        if (paths_token == NULL)
                return (NULL);
        return (paths_token);
}
/**
 * build_full_path - Combine a token in any tokens PATH array with a command.
 * @paths: Represents a token of the environment variable PATH.
 * @commande: the command.
 * Return: On success a full path of the command, Otherwise NULL.
 */
char *build_full_path(char *paths, char *commande)
{
        int pathlen;
        int commandelen;
        int rlen;
        char *built;

        if (paths == NULL || commande == NULL)
                return (NULL);
        pathlen = _strlen(paths);
        commandelen = _strlen(commande);
        rlen = pathlen + commandelen + 2;

        built = malloc(sizeof(char) * rlen);
        if (built == NULL)
                return (NULL);
        _strcpy_(built, paths);
        _strcat_(built, "/");
        _strcat_(built, commande);
        return (built);
}

/**
 * find_path_index - Find the index of an environment variable.
 * @envy: Environments variable that needs to be found.
 * Return: on success returns the index of the environment variable.
 * otherwise returns -1.
 */
int find_path_index(char *envy)
{
        int j;
        int rlen;
        int x;

        rlen = _strlen(envy);
        for (j = 0; environ[j] != NULL; j++)
        {
                for (x = 0; x < rlen; x++)
                {
                        if (environ[j][x] != envy[x])
                                break;
                }
                if (x == rlen && environ[j][x] == '=')
                        return (j);
        }
        return (-1);
}
