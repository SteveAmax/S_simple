#include "shell.h"

/**
 * _isdigit - checks for a digits
 *@c: num
 * Return: Always 0.
 */

int _isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	return (0);
}

/**
 * set_env - sets an environment variable with a value.
 * if it exist it modifies it if not it sets it.
 * @name: name of the variable.
 * @value: the value to set to the var name.
 */

void set_env(char *yname, char *xvalue_i)
{
	int index_n;
	char *vstr;
	char **en_vp = environ;
	int name_rlen, value_rlen, rlen;

	if (!yname || !xvalue_i)
	{
		perror("setenv()");
		return;
	}
	name_len = _strlen_i(yname);
	value_len = _strlen_i(xvalue_i);
	len = name_rlen + value_rlen + 2;

	vstr = malloc(rlen * sizeof(char));
	if (!vstr)
	{
		perror("Alloc fails");
		return;
	}
	_str_copy_i(vstr, yname), _str_cat_i(vstr, "="), _str_cat_i(vstr, xvalue_i);
	index = path_index_finder(yname);
	if (index_n != -1)
		environ[index_n] = vstr;
	else
	{
		while (*en_vp)
			en_vp++;
		*en_vp = vstr;
		en_vp++;
		*en_vp = NULL;
	}
}

/**
 * _atoi - convert a string to an integer
 * @s: str
 * Return: 0 if no number found and number otherwise
 */

int _atoi(char *s)
{
	int ix, di, nx, rlen, g, digit_i;

	ix = 0;
	di = 0;
	nx = 0;
	rlen = 0;
	g = 0;
	digit_i = 0;

	while (s[rlen] != '\0')
		rlen++;

	while (ix < rlen && g == 0)
	{
		if (s[ix] == '-')
			++di;

		if (s[ix] >= '0' && s[ix] <= '9')
		{
			digit_i = s[ix] - '0';
			if (di % 2)
				digit_i = -digit_i;
			n = n * 10 + digit_i;
			g = 1;
			if (s[ix + 1] < '0' || s[ix + 1] > '9')
				break;
			g = 0;
		}
		ix++;
	}
	if (g == 0)
		return (0);

	return (n);
}

/**
 * _isupper - checks for uppercase character
 * @c: char
 * Return: Always 0.
 */

int _isupper(int c)
{
	if (c <= 90 && c >= 65)
		return (1);

	return (0);
}

