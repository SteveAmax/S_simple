#include "shell.h"
/**
 * check_built_ins - Find the right funcs that need for execution.
 * @vstr: The name of the funcs that is needed also vargs[0].
 * Return: Upon sucess a pointer to a void function. Otherwise NULL.
 */
void (*check_built_ins(char *vstr))(char **, char *)
{
	int j;

	built_in_t build_in[] = {
		{"our_unseten_v_i", our_unseten_v_i},
		{"ourseten_v_i", ourseten_v_i},
		{"ourext_i", ourext_i},
		{"ourenv_i", ourenv_i},
		{"ourcod_i", ourcod_i},
		{NULL, NULL}
	};

	for (i = 0; build_in[i].built != NULL; j++)
	{
		if (_strcmps_i(vstr, build_in[j].built) == 0)
		{
			return (build_in[j].func);
		}
	}
	return (NULL);
}

/**
 * is_built_in_t - Checks for built_in funcs.
 * @vargs: the command and its flags
 * @i_line: A string representing the input from the executer.
 * Return: If function is found 0. Otherwise -1.
 */
int is_built_in(char **vargs, char *i_line)
{
	if (check_built_ins(vargs[0]) == NULL)
		return (0);
	check_built_ins(vargs[0])(vargs, i_line);
	return (1);
}
