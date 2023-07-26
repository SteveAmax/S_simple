#include "shell.h"

/**
 * print_commands - print elements of an array
 * @cmd: the array
 */
void print_commands(char **cmd)
{
	int j = 0;

	while (cmd[j])
	{
		printf("%s--------\n", cmd[j]);
		j++;
	}
}

