#include "shell.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


/**
 * execute_cmd - executes inputted command
 * @sts: pointer to shell status structure
 */
void execute_cmd(shell_sts_t *sts)
{
	pid_t exec_pid;
	int status;

	if (sts->tok_cmd == NULL)
		return;
	exec_pid = fork();
	if (exec_pid < 0)
		perror(sts->tok_cmd[0]);

	if (exec_pid == 0)
	{
		/* In the Child */
		execve(sts->tok_cmd[0], sts->tok_cmd, sts->envp);
		/* The rest is only executed in case of error (print it) */
		perror(sts->tok_cmd[0]);
		/* Avoiding memory leak in child process */
		clear_cmd_buffer(sts);
		clear_tok_cmd(sts);
		exit(98);
	}
	else
	{
		/* In the parent, await the child to complete execution */
		wait(&status);
	}
}
