#include "shell.h"
#include <string.h>
#include <unistd.h>

/**
 * clear_paths - Clears paths variable
 * @sts: pointer to shell status structure
 */
void clear_paths(shell_sts_t *sts)
{
	if (sts->paths != NULL)
	{
		if ((*sts->paths) != NULL)
			free(*(sts->paths));
		free(sts->paths);
		sts->paths = NULL;
	}
}

/**
 * clear_exec - Clears executable path variable
 * @sts: pointer to shell status structure
 */
void clear_exec(shell_sts_t *sts)
{
	if (sts->exec != NULL)
	{
		free(sts->exec);
		sts->exec = NULL;
	}
}

/**
 * tokenise_path - extracts tokens from the path string
 * @path: PATH string extracted from environment variables
 * @sts: pointer to shell status structure
 */
void tokenise_path(char *path, shell_sts_t *sts)
{
	char *pth = NULL, *cur = NULL;
	char *delimiters = " :\t\r\n";
	int cnt = 0;

	clear_paths(sts);
	if (path == NULL)
		return;
	pth = _strdup(path);
	if (pth == NULL)
		return;
	/* Get required length of tokens array */
	for (cur = pth; (*cur) != '\0'; cur++)
	{
		if (_strchr(delimiters, *cur) != NULL)
		{
			cnt++;
			/* To avoid counting consecutive delimiters */
			do {
				cur++;
			} while (((*cur) != '\0') && (_strchr(delimiters, *cur) != NULL));
		}
	}
	sts->paths = malloc(sizeof(char *) * (cnt + 1));
	if (sts->paths == NULL)
	{
		free(pth);
		return;
	}
	/* Storing the tokens of the string */
	sts->paths[0] = strtok(pth, delimiters);
	for (cnt = 0; sts->paths[cnt] != NULL;)
	{
		sts->paths[++cnt] = strtok(NULL, delimiters);
	}
	sts->paths[cnt] = NULL;
}

/**
 * retrieve_path - Gets the PATH environment variable
 * @sts: pointer to shell status structure
*/
void retrieve_path(shell_sts_t *sts)
{
	int cnt;

	/* looping through environment variables */
	for (cnt = 0; sts->envp[cnt] != NULL; cnt++)
	{
		/* once PATH is found */
		if (_strncmp(sts->envp[cnt], "PATH=", 5) == 0)
		{
			tokenise_path(&(sts->envp[cnt][5]), sts);
			return;
		}
	}
	clear_paths(sts);
}

/**
 * check_exec_path - checks whether there is an executable file with the
 *  provided name at any of the PATHs
 * @sts: pointer to shell status structure
 */
void check_exec_path(shell_sts_t *sts)
{
	int cnt, ind_p, ind_c;
	char *exec_path;

	clear_exec(sts);
	if ((sts->tok_cmd == NULL) || (sts->tok_cmd[0] == NULL))
		return;
	if ((sts->tok_cmd[0][0] == '.') || (sts->tok_cmd[0][0] == '/'))
	{
		if (access(sts->tok_cmd[0], F_OK | X_OK) == 0)
			sts->exec = _strdup(sts->tok_cmd[0]);
		return;
	}
	for (cnt = 0; ((sts->paths != NULL) && (sts->paths[cnt] != NULL)); cnt++)
	{
		/* Combining each PATH environment variable with the given command */
		exec_path = malloc(sizeof(char) * (_strlen(sts->paths[cnt]) +
			_strlen(sts->tok_cmd[0]) + 2));
		if (exec_path == NULL)
			return;
		for (ind_p = 0; sts->paths[cnt][ind_p] != '\0'; ind_p++)
			exec_path[ind_p] = sts->paths[cnt][ind_p];
		if (exec_path[ind_p - 1] != '/')
			exec_path[ind_p++] = '/';
		for (ind_c = 0; sts->tok_cmd[0][ind_c] != '\0'; ind_c++)
			exec_path[ind_p++] = sts->tok_cmd[0][ind_c];

		/* Checking if the combined path is an executable */
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			sts->exec = exec_path;
			return;
		}
		/* Avoid memory leaks */
		clear_exec(sts);
	}
}
