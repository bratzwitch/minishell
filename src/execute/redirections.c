#include "../../include/minishell.h"

void handle_special_tokens(t_token *tokens)
{
	t_token *current = tokens;
	t_token *list1 = NULL;
	t_token *list2 = NULL;
	t_redirection redir[] = {
		{TOKEN_REDIRECT_IN, input_redirection},
		{TOKEN_REDIRECT_OUT, output_redirection},
		{TOKEN_HEREDOC, heredoc_redirection},
		{TOKEN_REDIRECT_APPEND, append_redirection},
		{0, NULL}};
	int i;

	split_tokens(tokens, &list1, &list2, ft_is_special_token(tokens));
	concatenate_tokens(&tokens, list2->next);
	while (current)
	{
		i = 0;
		while (redir[i].handler != NULL)
		{
			if (current->type == redir[i].type && redir[i].type > 0)
			{
				split_tokens(current, &list1, &list2, redir[i].type);
				if (!list1 || !list1->value || !list2 || !list2->value)
				{
					fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n", current->value);
					return;
				}
				if (redir[i].handler(list2->value) == -1)
				{
					printf("Redirection failed for %s\n", strerror(errno));
					return;
				}
				current = list2;
				break;
			}
			i++;
		}
		current = current->next;
	}
}

// printf("This goes to the file\n");
// dup2(stdout_copy, STDOUT_FILENO);
// close(stdout_copy); // not closing file descriptors can lead to memory leaks
/*
O_WRONLY: This flag specifies that the file is opened for write-only access.
O_CREAT: This flag tells the system to create the file if it does not exist.
O_TRUNC: This flag clears its contents if it already exists.
0644: rw-r--r-- (Owner can read/write, group and others can read)

dup vs dup2
- dup duplicates an existing file descriptor to the lowest available file descriptor. E.g. int new_fd = dup(fd);
- dup2 allows you to specify exactly which file descriptor to duplicate to. E.g. dup2(fd,
	STDIN_FILENO);
stdin (standard input) is a predefined file descriptor (0) that a program uses to read input.
*/
