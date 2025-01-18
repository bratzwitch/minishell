/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:08 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 13:37:19 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirection *init_redirections(void)
{
    static t_redirection redir[] = {
        {TOKEN_REDIRECT_IN, input_redirection},
        {TOKEN_REDIRECT_OUT, output_redirection},
        {TOKEN_HEREDOC, heredoc_redirection},
        {TOKEN_REDIRECT_APPEND, append_redirection},
        {0, NULL}};
    return (redir);
}

int process_token(t_token *current, t_redirection *redir, t_token **list1, t_token **list2)
{
    int i = 0;

    while (redir[i].handler != NULL)
    {
        if (current->type == redir[i].type && redir[i].type > 0)
        {
            split_tokens(current, list1, list2, redir[i].type);
            if (redir[i].handler((*list2)->value) == -1)
                return (-1);
            return (1);
        }
        i++;
    }
    return (0);
}

void handle_special_tokens(t_token *tokens)
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
            return;
        if (processed == 1)
        {
            current = list2;
            continue;
        }
        current = current->next;
    }
    lst_cleanup(&current, free_token);
    split_tokens(tokens, &list1, &list2, ft_is_special_token(tokens));
}

// void handle_special_tokens(t_token *tokens)
// {
// 	t_token *current = tokens;
// 	t_token *list1 = NULL;
// 	t_token *list2 = NULL;
// 	t_redirection redir[] = {
// 		{TOKEN_REDIRECT_IN, input_redirection},
// 		{TOKEN_REDIRECT_OUT, output_redirection},
// 		{TOKEN_HEREDOC, heredoc_redirection},
// 		{TOKEN_REDIRECT_APPEND, append_redirection},
// 		{0, NULL}};
// 	int i;

// 	while (current)
// 	{
// 		i = 0;
// 		while (redir[i].handler != NULL)
// 		{
// 			if (current->type == redir[i].type && redir[i].type > 0)
// 			{
// 				split_tokens(current, &list1, &list2, redir[i].type);
// 				if (redir[i].handler(list2->value) == -1)
// 					return;
// 				current = list2;
// 				break;
// 			}
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	lst_cleanup(&current, free_token);
// 	split_tokens(tokens, &list1, &list2, ft_is_special_token(tokens));
// 	// concatenate_tokens(&list1, list2->next);
// }
