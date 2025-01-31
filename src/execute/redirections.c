/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:08 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 09:11:12 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirection *init_redirections(void)
{
	static t_redirection redir[] = {{TOKEN_REDIRECT_IN, input_redirection},
									{TOKEN_REDIRECT_OUT, output_redirection},
									{TOKEN_HEREDOC, heredoc_redirection_wrapper},
									{TOKEN_REDIRECT_APPEND, append_redirection},
									{0, NULL}};

	return (redir);
}

int process_token(t_token *current, t_redirection *redir, t_token **list1,
				  t_token **list2)
{
	int i;

	i = 0;
	while (redir[i].handler != NULL)
	{
		if (current->type == redir[i].type && redir[i].type > 0)
		{
			if (current->type == TOKEN_HEREDOC)
			{
				split_tokens(current, list1, list2, redir[i].type);
				if (handle_heredoc(*list2) == -1)
					return (-1);
			}
			else
			{
				split_tokens(current, list1, list2, redir[i].type);
				if (redir[i].handler((*list2)->value) == -1)
					return (-1);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void lst_print(t_token *head)
{
	t_token *current = head;
	while (current != NULL)
	{
		printf("Type: %d, Value: %s -> ", current->type, current->value);
		current = current->next;
	}
	printf("NULL\n");
}

int handle_special_tokens(t_token *tokens)
{
	t_token *current;
	t_token *list1;
	t_token *list2;
	t_redirection *redir;
	int processed;

	current = tokens;
	list1 = NULL;
	list2 = NULL;
	redir = init_redirections();
	while (current)
	{
		processed = process_token(current, redir, &list1, &list2);
		if (processed == -1)
		{
			split_free(tokens, &list1, &list2, ft_is_special_token(tokens));
			lst_cleanup(&list2, free_token);
			return (-1);
		}
		if (processed == 1)
		{
			current = list2;
			continue;
		}
		current = current->next;
	}
	split_free(tokens, &list1, &list2, ft_is_special_token(tokens));
	// lst_cleanup(&list2, free_token);
	return (1);
}
