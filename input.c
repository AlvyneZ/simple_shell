#include "shell.h"
#include <unistd.h>
#include <stdio.h>

/**
 * clear_cmd_buffer - Clears current command buffer
 * @sts: pointer to shell status structure
 */
void clear_cmd_buffer(shell_sts_t *sts)
{
	if (sts->cur_cmd != NULL)
	{
		free(sts->cur_cmd);
		sts->cur_cmd = NULL;
	}
}

/**
 * get_command - Gets command from input stream
 * @sts: pointer to shell status structure
 *
 * Return: characters read on success, -1 otherwise
 */
int get_command(shell_sts_t *sts)
{
	/* Prompting user for input if in interactive mode */
	if (sts->interactive_md)
		write(STDOUT_FILENO, "#simple_shell$ ", 15);

	clear_cmd_buffer(sts);
	sts->cur_cmd_len = getline(&(sts->cur_cmd), &(sts->cur_cmd_sz), stdin);
	return (sts->cur_cmd_len);
}
