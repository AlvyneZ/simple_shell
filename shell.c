#include "shell.h"
#include <unistd.h>
#include <stdio.h>

/**
 * main - simple REPL shell program
 * @argc: Number of command line arguments
 * @argv: Array of strings of command line arguments
 * @envp: Array of strings of the environment
 * Return: 0 on success
*/
int main(int argc, char **argv, char **envp)
{
	shell_sts_t sts = {0};

	(void)argc;
	(void) argv;
	sts.envp = envp;
	sts.interactive_md = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));

	do {
		if (get_command(&sts) == 1) /* Empty line */
			continue;
		if (sts.cur_cmd_len <= 0) /* Error or End of file */
		{
			printf("\nexit\n");
			break;
		}
		tokenise_cmd(&sts);
		execute_cmd(&sts);
		clear_cmd_buffer(&sts);
		clear_tok_cmd(&sts);
	} while (sts.interactive_md);

	clear_cmd_buffer(&sts);
	clear_tok_cmd(&sts);

	return (0);
}
