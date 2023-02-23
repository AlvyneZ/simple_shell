#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/**
 * handle_signal - Handles SIGINT (CTRL+C) and allows graceful exit
 * @signal_number: signal number associated with signal
 */
void handle_signal(int signal_number)
{
	/* declaring the signal number as unused variable */
	(void)signal_number;

	/* writing to the terminal to revert to non-interactive */
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "# ", 2);
}

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
	sts.sh_name = argv[0];
	sts.envp = envp;
	sts.interactive_md = (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
	retrieve_path(&sts);
	signal(SIGINT, handle_signal);

	do {
		if (get_command(&sts) == 1) /* Empty line */
			continue;
		if (handle_builtin(&sts))
			continue;
		tokenise_cmd(&sts);
		check_exec_path(&sts);
		execute_cmd(&sts);
	} while (sts.interactive_md);

	clear_cmd_buffer(&sts);
	clear_tok_cmd(&sts);
	clear_exec(&sts);
	clear_paths(&sts);
	return (0);
}
