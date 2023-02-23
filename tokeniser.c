#include "shell.h"
#include <string.h>

/**
 * clear_tok_cmd - Clears current tokenized command buffer
 * @sts: pointer to shell status structure
 */
void clear_tok_cmd(shell_sts_t *sts)
{
	if (sts->tok_cmd != NULL)
	{
		free(sts->tok_cmd);
		sts->tok_cmd = NULL;
	}
}

/**
 * tokenise_cmd - extracts tokens from the command string
 * @sts: pointer to shell status structure
 */
void tokenise_cmd(shell_sts_t *sts)
{
	char *cur = NULL;
	char *delimiters = " \t\r\n";
	int cnt = 0;

	clear_tok_cmd(sts);
	if (sts->cur_cmd == NULL)
		return;
	/* Get required length of tokens array */
	for (cur = sts->cur_cmd; (*cur) != '\n'; cur++)
	{
		if (_strchr(delimiters, *cur) != NULL)
		{
			/* To avoid counting delimiters at the beginning of command */
			if (cur != sts->cur_cmd)
				cnt++;
			/* To avoid counting consecutive delimiters */
			do {
				cur++;
			} while (((*cur) != '\0') && (_strchr(delimiters, *cur) != NULL));
		}
	}
	sts->tok_cmd = malloc(sizeof(char *) * (cnt + 2));
	if (sts->tok_cmd == NULL)
		return;
	/* Storing the tokens of the string */
	sts->tok_cmd[0] = strtok(sts->cur_cmd, delimiters);
	for (cnt = 0; sts->tok_cmd[cnt] != NULL;)
	{
		sts->tok_cmd[++cnt] = strtok(NULL, delimiters);
	}
	sts->tok_cmd[cnt] = NULL;
}
