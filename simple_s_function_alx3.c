#include "shell.h"

/**
 * _isdigit_ - checks the code digit
 *@y: num
 * Return: Always 0.
 */

int _isdigit_(int y)
{
        if (y <= 57 && y >= 48)
                return (1);
        return (0);
}

/**
 * set_env - sets an envi variable with a value.
 * if it exist it modifies it if not it sets it.
 * @na: name of the variable.
 * @valu: the value to set to the var name.
 */

void set_env(char *na, char *valu)
{
        int index;
        char *rts;
        char **envo = environ;
        int na_rlen, valu_rlen, rlen;

        if (!na || !valu)
        {
                perror("setenv()");
                return;
        }
        na_rlen = _strlen(na);
        valu_rlen = _strlen(valu);
        rlen = na_rlen + valu_rlen + 2;

        rts = malloc(rlen * sizeof(char));
        if (!rts)
        {
                perror("Alloc fails");
                return;
        }
        _strcpy_(rts, na), _strcat_(rts, "="), _strcat_(rts, valu);
        index = find_path_index(na);
        if (index != -1)
                environ[index] = rts;
        else
        {
                while (*envo)
                        envo++;
                *envo = rts;
                envo++;
                *envo = NULL;
        }
}

/**
 * _atoi - converture of string to an integer
 * @v: string
 * Return: 0 if no number found and number otherwise
 */

int _atoi(char *v)
{
        int i, ds, ne, elen, ff, sdigit;

        i = 0;
        ds = 0;
        ne = 0;
        elen = 0;
        ff = 0;
        sdigit = 0;

        while (v[elen] != '\0')
                elen++;

        while (i < elen && ff == 0)
        {
                if (v[i] == '-')
                        ++ds;

                if (v[i] >= '0' && v[i] <= '9')
                {
                        sdigit = v[i] - '0';
                        if (ds % 2)
                                sdigit = -sdigit;
                        ne = ne * 10 + sdigit;
                        ff = 1;
                        if (v[i + 1] < '0' || v[i + 1] > '9')
                                break;
                        ff = 0;
                }
                i++;
        }
        if (ff == 0)
                return (0);

        return (ne);
}

/**
 * _isupper - checks for uppercase character
 * @ch: char
 * Return: Always 0.
 */

int _isupper(int ch)
{
        if (ch <= 90 && ch >= 65)
                return (1);

        return (0);
}
