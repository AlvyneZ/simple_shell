#include "shell.h"
#include <unistd.h>
#include <stdio.h>

/**
 * main - simple REPL shell program
 * @argc: Number of command line arguments
 * @argv: Array of strings of command line arguments
 * Return: 0 on success
*/
int main(int argc, char **argv)
{
	shell_sts_t sts = {0};

	(void)argc;
	(void) argv;
	sts.interactive_md = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));

	do {
		if (get_command(&sts) == 1) /* Empty line */
			continue;
		if (sts.cur_cmd_len <= 0) /* Error or End of file */
		{
			printf("\nexit\n");
			break;
		}
		printf("%s", sts.cur_cmd);
	} while (sts.interactive_md);

	clear_cmd_buffer(&sts);

	return (0);
}
