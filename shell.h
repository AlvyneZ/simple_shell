#ifndef SHELL_HEADER_INCLUDE_
#define SHELL_HEADER_INCLUDE_

#include <stdlib.h>

/**
 * struct shell_sts_s - Structure for storing the shell program status
 * @interactive_md: boolean for interactive mode of shell
 * @cur_cmd: Current command to be executed
 * @cur_cmd_sz: Size of current command buffer
 * @cur_cmd_len: current command data length
 * @tok_cmd: Tokenized current command
 * @envp: Array of strings of the environment
 *
 * Description: This struct is passed to most functions of the program as
 *  an alternative to global variables
*/
struct shell_sts_s
{
	int interactive_md;
	char *cur_cmd;
	size_t cur_cmd_sz;
	ssize_t cur_cmd_len;
	char **tok_cmd;
	char **envp;
};

typedef struct shell_sts_s shell_sts_t;

/* Defined in str_functions.c */
int _strlen(char *s);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);

/* Defined in input.c */
void clear_cmd_buffer(shell_sts_t *sts);
int get_command(shell_sts_t *sts);

/* Defined in tokeniser.c */
void clear_tok_cmd(shell_sts_t *sts);
void tokenise_cmd(shell_sts_t *sts);

/* Defined in execution.c */
void execute_cmd(shell_sts_t *sts);

#endif /* SHELL_HEADER_INCLUDE_ */
