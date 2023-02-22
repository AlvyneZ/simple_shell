#include "shell.h"
#include <unistd.h>

/**
* _strcmp - Compares two strings
 * @s1: First string
 * @s2: second string
 * Return: Lexicographic difference of the strings
 */
int _strcmp(char *s1, char *s2)
{
	int ind;

	for (ind = 0; ((s1[ind] != '\0') && (s2[ind] != '\0')); ind++)
	{
		if (s1[ind] - s2[ind])
			return (s1[ind] - s2[ind]);
	}

	return (s1[ind] - s2[ind]);
}

/**
 * handle_builtin - handles execution of builtin functions
 * @sts: pointer to shell status structure
 *
 * Return: 1 if executed, 0 if not
 */
int handle_builtin(shell_sts_t *sts)
{
	int cnt;
	char *env_str = "env\n", *exit_str = "exit\n";

	/* checking for string matching with env || exit */
	if (_strcmp(sts->cur_cmd, env_str) == 0)
	{
		for (cnt = 0; sts->envp[cnt] != NULL; cnt++)
		{
			write(STDOUT_FILENO, sts->envp[cnt], _strlen(sts->envp[cnt]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (1);
	}
	else if (_strcmp(sts->cur_cmd, exit_str) == 0)
	{
		clear_cmd_buffer(sts);
		clear_tok_cmd(sts);
		clear_exec(sts);
		clear_paths(sts);
		exit(0);
	}
	return (0);
}
