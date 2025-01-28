/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:54:13 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/28 11:15:04 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_pipe(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int count_heredocs(t_token *token_list)
{
	int count = 0;
	t_token *tmp = token_list;

	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int heredoc_redirection_wrapper(const char *param)
{
	(void)param;
	return(0);
}
