#include "shell.h"

/**
 * main - Entry point of the program
 * @vargc: varg count
 * @cargv: carg vector
 * @envy: the inviron is variable.
 * Return: Always 0 on success.
 */
int main(__attribute__((unused)) int vargc, char *cargv[], char *envy[])
{
	signal(SIGINT, SIG_IGN);
	if (isatty(STDIN_FILENO) == 1)
	{
		interac_tive_i(cargv, envy);
	}
	else
		batch(vargv, envy);
	return (0);
}

/**
 * interac_tive_i - execute command on the mode interactive.
 * @argv: argument vector
 * @envy: environ variable.
 */
void interac_tive_i(char *cargv[], char *envy[])
{
	char *i_line, **vargs, *cmd_full_path;
	int cmd_counter_i = 1;
	struct stat statbuf;

	while (1)
	{
		write(STDOUT_FILENO, "#Home$ ", 7);
		fflush(stdout);
		i_line = you_readline_i(), vargs = prase_yline_i(i_line, DLMT);
		if (!vargs[0])
		{
			free_i(i_line), free_arri(vargs);
			continue;
		}
		else if (!is_built_in(vargs, i_line))
		{
			cmd_full_path = search_full_path(vargs[0]);
			if (cmd_full_path || (stat(vargs[0], &statbxf) == 0))
			{
				if (cmd_full_path)
				{
					vargs[0] = _strd_up_i(cmd_full_path);
					free_i(cmd_full_path);
				}
				create_process(vargs, envy);
			}
			else
				error_handl_i(vargv, vargs, cmd_counter_i);
			free_i(i_line), free_arri(vargs), cmd_counter_i++;
		}
		else
		{
			free_i(i_line), free_arri(vargs);
		}
	}
}

/**
 * batch - executing command on the mode non-inter active.
 * @cargv: argument vector
 * @envy: environ variable.
 */

void batch(char *cargv[], char *envy[])
{
	char *i_line, **vargs, *cmd_full_path;
	int cmd_counter_i = 1;
	struct stat statbxf;

	i_line = you_readline_i();
	vargs = prase_yline_i(i_line, DLMT);
	if (!vargs[0])
	{
		free_i(i_line);
		free_arri(vargs);
	}
	else if (!is_built_in(vargs, i_line))
	{
		cmd_full_path = search_full_path(vargs[0]);
		if (cmd_full_path || (stat(vargs[0], &statbxf) == 0) ||
				(access(vargs[0], X_OK) == 0))
		{
			if (cmd_full_path)
			{
				free_i(args[0]);
				args[0] = _strd_up_i(cmd_full_path);
				free_i(cmd_full_path);
			}
		create_process(args, env);
		}
		else
			error_handl_i(cargv, vargs, cmd_counter_i);
		free_i(i_line);
		free_arri(vargs);
		cmd_counter_i++;
	}
	else
	{
		free_i(i_line);
		free_arri(vargs);
	}
}
