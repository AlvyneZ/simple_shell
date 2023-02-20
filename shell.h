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
};

typedef struct shell_sts_s shell_sts_t;

void clear_cmd_buffer(shell_sts_t *sts);
int get_command(shell_sts_t *sts);

#endif /* SHELL_HEADER_INCLUDE_ */
