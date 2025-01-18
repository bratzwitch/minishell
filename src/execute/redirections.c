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

	while (current)
	{
		i = 0;
		while (redir[i].handler != NULL)
		{
			if (current->type == redir[i].type && redir[i].type > 0)
			{
				split_tokens(current, &list1, &list2, redir[i].type);
				lst_print(list1);
				lst_print(list2);
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
	lst_cleanup(&current,free_token);
	split_tokens(tokens, &list1, &list2, ft_is_special_token(tokens));
	// concatenate_tokens(&list1, list2->next);
}
