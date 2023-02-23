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
		write(STDOUT_FILENO, "# ", 2);

	clear_cmd_buffer(sts);
	errno = 0;
	sts->cur_cmd_len = getline(&(sts->cur_cmd), &(sts->cur_cmd_sz), stdin);

	if (sts->cur_cmd_len <= 0) /* Error or End of file */
	{
		clear_cmd_buffer(sts);
		clear_tok_cmd(sts);
		clear_exec(sts);
		clear_paths(sts);
		if (errno == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(0);
		}
		else
		{
			perror(sts->sh_name);
			exit(98);
		}
	}

	return (sts->cur_cmd_len);
}
